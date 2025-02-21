///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Resources/AssetsManager.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
AssetsManager* AssetsManager::m_instance = nullptr;

///////////////////////////////////////////////////////////////////////////////
AssetsManager::AssetsManager(const String& assets)
    : m_packer(Z_BEST_COMPRESSION)
{
    try {
        m_packer.unpack(assets);
    } catch (const std::exception& error) {
        std::cerr << "Assets: " << error.what() << std::endl;
    }
    if (AssetsManager::m_instance)
        delete AssetsManager::m_instance;
    AssetsManager::m_instance = this;
}

///////////////////////////////////////////////////////////////////////////////
AssetsManager* AssetsManager::getInstance(void)
{
    if (!AssetsManager::m_instance)
        AssetsManager::m_instance = new AssetsManager();
    return (AssetsManager::m_instance);
}

///////////////////////////////////////////////////////////////////////////////
SPtr<sf::Image> AssetsManager::getImage(const String& key)
{
    auto it = m_imageCache.find(key);
    if (it != m_imageCache.end())
        return (it->second);
    auto image = m_packer.getImage(key);
    if (!image)
        return (nullptr);
    m_imageCache[key] = *image;
    return (*image);
}

///////////////////////////////////////////////////////////////////////////////
SPtr<sf::Texture> AssetsManager::getTexture(const String& key)
{
    auto it = m_textureCache.find(key);
    if (it != m_textureCache.end())
        return (it->second);
    auto texture = m_packer.getTexture(key);
    if (!texture)
        return (nullptr);
    m_textureCache[key] = *texture;
    return (*texture);
}

///////////////////////////////////////////////////////////////////////////////
SPtr<sf::SoundBuffer> AssetsManager::getSound(const String& key)
{
    auto it = m_soundCache.find(key);
    if (it != m_soundCache.end())
        return (it->second);
    auto sound = m_packer.getSound(key);
    if (!sound)
        return (nullptr);
    m_soundCache[key] = *sound;
    return (*sound);
}

///////////////////////////////////////////////////////////////////////////////
SPtr<sf::Font> AssetsManager::getFont(const String& key)
{
    auto it = m_fontCache.find(key);
    if (it != m_fontCache.end())
        return (it->second);
    auto font = m_packer.getFont(key);
    if (!font)
        return (nullptr);
    m_fontCache[key] = *font;
    return (*font);
}

///////////////////////////////////////////////////////////////////////////////
SPtr<Data> AssetsManager::getData(const String& key)
{
    auto it = m_dataCache.find(key);
    if (it != m_dataCache.end())
        return (it->second);
    auto data = m_packer.getData(key);
    if (!data)
        return (nullptr);
    m_dataCache[key] = *data;
    return (*data);
}

///////////////////////////////////////////////////////////////////////////////
bool AssetsManager::unloadImage(const String& key)
{
    return (m_imageCache.erase(key) > 0);
}

///////////////////////////////////////////////////////////////////////////////
bool AssetsManager::unloadTexture(const String& key)
{
    return (m_textureCache.erase(key) > 0);
}

///////////////////////////////////////////////////////////////////////////////
bool AssetsManager::unloadSound(const String& key)
{
    return (m_soundCache.erase(key) > 0);
}

///////////////////////////////////////////////////////////////////////////////
bool AssetsManager::unloadFont(const String& key)
{
    return (m_fontCache.erase(key) > 0);
}

///////////////////////////////////////////////////////////////////////////////
bool AssetsManager::unloadData(const String& key)
{
    return (m_dataCache.erase(key) > 0);
}


///////////////////////////////////////////////////////////////////////////////
bool AssetsManager::unloadAsset(const String& key)
{
    bool unloaded = false;
    unloaded |= unloadImage(key);
    unloaded |= unloadTexture(key);
    unloaded |= unloadSound(key);
    unloaded |= unloadFont(key);
    unloaded |= unloadData(key);
    return (unloaded);
}

///////////////////////////////////////////////////////////////////////////////
void AssetsManager::clearCache(void)
{
    m_imageCache.clear();
    m_textureCache.clear();
    m_soundCache.clear();
    m_fontCache.clear();
    m_dataCache.clear();
}

///////////////////////////////////////////////////////////////////////////////
Uint64 AssetsManager::getCacheSize(void) const
{
    return (
        m_imageCache.size() +
        m_textureCache.size() +
        m_soundCache.size() +
        m_fontCache.size() +
        m_dataCache.size()
    );
}

} // namespace tkd
