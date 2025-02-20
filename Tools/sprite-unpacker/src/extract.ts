/** Dependencies */
import type { UnitySprite } from './types';
import type { Image } from 'canvas';
import { createCanvas } from 'canvas';
import fs from 'fs';
import path from 'path';

/**
 * Extract a specific sprite from a sprite atlas
 * @param atlas The sprite atlas containing the sprite
 * @param sprite The sprite data to extract
 * @param outputPath the result path
 */
export const extractSprite = (atlas: Image, sprite: UnitySprite, outputPath: string) => {
  const { width, height, x, y } = sprite.Sprite.m_Rect;

  const canvas = createCanvas(width, height);
  const contxt = canvas.getContext('2d');

  contxt.drawImage(atlas, x, atlas.height - y - height, width, height, 0, 0, width, height);

  if (!fs.existsSync(outputPath))
    fs.mkdirSync(outputPath, { recursive: true });

  const buffer = canvas.toBuffer('image/png');

  const basename = sprite.Sprite.m_Name;
  let filePath = `${basename}.png`;

  fs.writeFileSync(path.join(outputPath, filePath), buffer);
};
