///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Resources/AssetsPacker.hpp>
#include <Engine/Resources/Compressor.hpp>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <filesystem>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
#define RCASTOF(arg) reinterpret_cast<char*>(&arg), sizeof(arg)
#define CRCASTOF(arg) reinterpret_cast<const char*>(&arg), sizeof(arg)

///////////////////////////////////////////////////////////////////////////////
const char* AssetsPacker::ASSETS_SIGNATURE = "TKDASSETS";

///////////////////////////////////////////////////////////////////////////////
AssetsPacker::AssetsPacker(int compressionLevel)
    : m_compressionLevel(compressionLevel)
{}

///////////////////////////////////////////////////////////////////////////////
AssetsPacker& AssetsPacker::operator<<(const Pair<String, Path>& entry)
{
    const String& key = entry.first;
    const Path& filepath = entry.second;

    Type type = AssetsPacker::getType(filepath);
    if (type == Type::Unknown)
        throw std::runtime_error("Unknown asset type: " + filepath.string());

    std::ifstream file(filepath, std::ios::binary);
    if (!file)
        throw std::runtime_error("Cannot open file: " + filepath.string());

    Data raw = Data(std::istreambuf_iterator<char>(file), {});
    Data data = Compressor::compress(raw, m_compressionLevel);

    Assets asset{data, raw.size(), data.size(), type};

    m_assets[key] = std::move(asset);

    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
AssetsPacker::Type AssetsPacker::getType(const Path& filepath)
{
    String ext = filepath.extension().string();

    if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
        return (Type::Image);
    if (ext == ".wav" || ext == ".ogg" || ext == ".flac")
        return (Type::Sound);
    if (ext == ".ttf" || ext == ".otf")
        return (Type::Font);
    if (ext == ".bin" || ext == ".dat")
        return (Type::Data);
    return (Type::Unknown);
}

///////////////////////////////////////////////////////////////////////////////
String AssetsPacker::formatSize(Uint64 size)
{
    const char* units[] = {"o", "Ko", "Mo", "Go"};
    int idx = 0;
    double fSize = static_cast<double>(size);

    while (fSize >= 1024.0 && idx < 3) {
        fSize /= 1024.0;
        idx++;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << fSize << " " << units[idx];
    return (oss.str());
}

///////////////////////////////////////////////////////////////////////////////
void AssetsPacker::pack(const String& filename) const
{
    std::ofstream out(filename, std::ios::binary);
    if (!out)
        throw std::runtime_error("Cannot open file: " + filename);

    // Write the assets signature
    out.write(ASSETS_SIGNATURE, 9);

    // Write the number of assets
    Uint32 count = static_cast<Uint32>(m_assets.size());
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& [key, asset] : m_assets) {
        // Write the asset key length and key
        Uint32 length = static_cast<Uint32>(key.size());
        out.write(CRCASTOF(length));
        out.write(key.data(), length);

        // Write the asset type
        out.write(CRCASTOF(asset.type));
        // Write the original asset data size
        out.write(CRCASTOF(asset.originalSize));
        // Write the compressed asset data size
        out.write(CRCASTOF(asset.compressedSize));

        // Write the compressed data
        out.write(
            reinterpret_cast<const char*>(asset.data.data()),
            asset.compressedSize
        );
    }

    out.close();
};

///////////////////////////////////////////////////////////////////////////////
void AssetsPacker::unpack(const String& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
        throw std::runtime_error("Cannot open file: " + filename);

    // Read the signature of the file
    char signature[9];
    in.read(signature, 9);
    if (std::string(signature, 9) != ASSETS_SIGNATURE)
        throw std::runtime_error("Invalid asset file signature");

    // Read the number of assets in the file
    Uint32 count = 0;
    in.read(RCASTOF(count));

    // Clear the previous assets
    m_assets.clear();

    for (Uint32 i = 0; i < count; i++) {
        // Read the key length and the key
        Uint32 length = 0;
        in.read(RCASTOF(length));
        std::string key(length, '\0');
        in.read(key.data(), length);

        // Read the type of the asset
        Type type;
        in.read(RCASTOF(type));

        // Read the original data size of the asset
        size_t originalSize;
        in.read(RCASTOF(originalSize));

        // Read the compressed data size of the asset
        size_t compressedSize;
        in.read(RCASTOF(compressedSize));

        // Create a new asset base on the size and type
        Assets asset{{}, originalSize, compressedSize, type};

        // Read the compressed data
        asset.data.resize(compressedSize);
        in.read(reinterpret_cast<char*>(asset.data.data()), compressedSize);

        // Save the asset in the map of assets
        m_assets[key] = std::move(asset);
    }

    in.close();
};

///////////////////////////////////////////////////////////////////////////////
Optional<SPtr<sf::Image>> AssetsPacker::getImage(const String& key) const
{
    auto it = m_assets.find(key);
    if (it == m_assets.end() || it->second.type != Type::Image)
        return (std::nullopt);

    auto data = Compressor::decompress(
        it->second.data,
        it->second.originalSize
    );

    return (std::make_shared<sf::Image>(data.data(), data.size()));
}

///////////////////////////////////////////////////////////////////////////////
Optional<SPtr<sf::Texture>> AssetsPacker::getTexture(const String& key) const
{
    auto it = m_assets.find(key);
    if (it == m_assets.end() || it->second.type != Type::Image)
        return (std::nullopt);

    auto data = Compressor::decompress(
        it->second.data,
        it->second.originalSize
    );

    return (std::make_shared<sf::Texture>(data.data(), data.size()));
}

///////////////////////////////////////////////////////////////////////////////
Optional<SPtr<sf::SoundBuffer>> AssetsPacker::getSound(const String& key) const
{
    auto it = m_assets.find(key);
    if (it == m_assets.end() || it->second.type != Type::Sound)
        return (std::nullopt);

    auto data = Compressor::decompress(
        it->second.data,
        it->second.originalSize
    );

    return (std::make_shared<sf::SoundBuffer>(data.data(), data.size()));
}

///////////////////////////////////////////////////////////////////////////////
Optional<SPtr<sf::Font>> AssetsPacker::getFont(const String& key) const
{
    auto it = m_assets.find(key);
    if (it == m_assets.end() || it->second.type != Type::Font)
        return (std::nullopt);

    auto data = Compressor::decompress(
        it->second.data,
        it->second.originalSize
    );

    return (std::make_shared<sf::Font>(data.data(), data.size()));
}

///////////////////////////////////////////////////////////////////////////////
Optional<SPtr<Data>> AssetsPacker::getData(const String& key) const
{
    auto it = m_assets.find(key);
    if (it == m_assets.end() || it->second.type != Type::Data)
        return (std::nullopt);

    auto data = Compressor::decompress(
        it->second.data,
        it->second.originalSize
    );

    return (std::make_shared<Data>(data));
}

///////////////////////////////////////////////////////////////////////////////
void AssetsPacker::addAsset(const String& key, const Path& filepath)
{
    *this << std::make_pair(key, filepath);
}

///////////////////////////////////////////////////////////////////////////////
UMap<String, AssetsPacker::Assets> AssetsPacker::getAssets(void) const
{
    return (m_assets);
}

///////////////////////////////////////////////////////////////////////////////
void AssetsPacker::clear(void)
{
    m_assets.clear();
}

///////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const AssetsPacker& packer)
{
    std::unordered_map<
        std::string, AssetsPacker::Assets
    > assets = packer.getAssets();
    size_t size = assets.size(), idx = 0;

    os << '[' << size << ']' << std::endl;

    size_t length = 0;
    for (const auto& [key, _] : assets) {
        if (key.length() > length)
            length = key.length();
    }

    os << std::setprecision(3);
    for (const auto& [key, asset] : assets) {
        if (idx != size - 1)
            os << " ├─ ";
        else
            os << " └─ ";

        if (asset.type == AssetsPacker::Type::Image)
            os << "\033[1;32m█\033[1;0m";
        else if (asset.type == AssetsPacker::Type::Sound)
            os << "\033[1;36m█\033[1;0m";
        else if (asset.type == AssetsPacker::Type::Font)
            os << "\033[1;35m█\033[1;0m";
        else if (asset.type == AssetsPacker::Type::Data)
            os << "\033[1;33m█\033[1;0m";

        os << ' ' << key;
        for (size_t i = key.length(); i < length + 4; i++)
            os << ' ';
        os  << AssetsPacker::formatSize(asset.compressedSize) << std::endl;
        idx++;
    }
    os << std::defaultfloat;
    return (os);
}

} // namespace tkd
