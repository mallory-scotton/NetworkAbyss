/** Dependencies */
import YAML from 'yaml';
import { discoverFiles } from './discover';
import type { UnitySprite, UnityTexture } from './types';
import fs from 'fs';
import path from 'path';
import Progress from 'ts-progress';
import { loadImage } from 'canvas';
import { extractSprite } from './extract';

function makeNamesUnique(sprites: UnitySprite[]) {
  const nameCount: { [key: string]: number } = {};

  return sprites.map((sprite) => {
    const originalName = sprite.Sprite.m_Name;
    let uniqueName = originalName;

    if (nameCount[originalName]) {
      nameCount[originalName]++;
      uniqueName = `${originalName}_${String(nameCount[originalName]).padStart(3, '0')}`;
    } else {
      nameCount[originalName] = 1;
    }

    sprite.Sprite.m_Name = uniqueName;
    return sprite;
  });
}

(async () => {
  if (process.argv.length <= 2) return console.error('Usage: start <AssetsFolder>');

  const assetsFolder = process.argv[2];
  const spriteFolder = path.join(assetsFolder, 'Sprite');
  const textureFolder = path.join(assetsFolder, 'Texture2D');

  if (!fs.existsSync(assetsFolder))
    return console.error('Cannot find the assets folder:', assetsFolder);
  if (!fs.existsSync(spriteFolder))
    return console.error('Cannot find the sprites folder:', spriteFolder);
  if (!fs.existsSync(textureFolder))
    return console.error('Cannot find the textures folder:', textureFolder);

  let Sprites: UnitySprite[];
  let Textures: UnityTexture[];

  if (!fs.existsSync('.sprites')) {
    const files = discoverFiles(spriteFolder, '.asset');
    var progress = Progress.create({ total: files.length, title: 'Caching Sprites' });
    var current = 0;

    Sprites = files.map((f) => {
      current++;
      progress.update();
      const content = fs.readFileSync(f, { encoding: 'utf-8' });
      return YAML.parse(content, { logLevel: 'silent', stringKeys: true }) as UnitySprite;
    });

    fs.writeFileSync('.sprites', JSON.stringify(Sprites), { encoding: 'utf-8' });
    progress.done();
  } else {
    console.log('[USUP] Sprites caching found, reading...');
    Sprites = JSON.parse(fs.readFileSync('.sprites', { encoding: 'utf-8' }));
    console.log('[USUP] Caching readed! Found', Sprites.length, 'sprites');
  }
  if (!fs.existsSync('.textures')) {
    const files = discoverFiles(textureFolder, '.meta');
    var progress = Progress.create({ total: files.length, title: 'Caching Textures' });
    var current = 0;

    Textures = files.map((f) => {
      current++;
      progress.update();
      const content = fs.readFileSync(f, { encoding: 'utf-8' });
      return {
        path: f,
        ...YAML.parse(content, { logLevel: 'silent', stringKeys: true })
      } as UnityTexture;
    });

    fs.writeFileSync('.textures', JSON.stringify(Textures), { encoding: 'utf-8' });
    progress.done();
  } else {
    console.log('[USUP] Textures caching found, reading...');
    Textures = JSON.parse(fs.readFileSync('.textures', { encoding: 'utf-8' }));
    console.log('[USUP] Caching readed! Found', Textures.length, 'textures');
  }

  let textureProgress = Progress.create({ total: Textures.length, title: 'Extracting Atlas...' });
  for (let i = 0; i < Textures.length; i++) {
    const texture = Textures[i];
    const basename = path.basename(texture.path.replace('.png.meta', ''));

    const sprites = makeNamesUnique(Sprites.filter((s) => s.Sprite.m_RD.texture.guid === texture.guid));
    const atlas = await loadImage(texture.path.replace('.meta', ''));

    let progress = Progress.create({ total: sprites.length, title: `Extacting ${basename}` });
    let subfolder = '';
    if (sprites.length !== 1) subfolder = basename;
    for (let i = 0; i < sprites.length; i++) {
      const sprite = sprites[i];
      progress.update();
      extractSprite(atlas, sprite, `output/${subfolder}`);
    }
    progress.done();
    textureProgress.update();
  }
  textureProgress.done();
})();
