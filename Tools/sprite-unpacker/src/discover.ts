/** Dependencies */
import fs from 'fs';
import path from 'path';

/**
 * Discover files in a folder filtered by an extension
 * @param folderPath the path to the folder to look for
 * @param extension The extension to look for
 * @returns The list of files absolute path in the folders
 */
export const discoverFiles = (folderPath: string, extension: string) => {
  return fs
    .readdirSync(folderPath, { encoding: 'utf-8' })
    .filter((file) => path.extname(file) === extension)
    .map((file) => path.join(folderPath, file))
};
