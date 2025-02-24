/** Dependencies */
import fs from 'fs';
import path from 'path';

const organizeSprites = (directoryPath: string) => {
  fs.readdir(directoryPath, (err, files) => {
    if (err) {
      console.error(`Error reading directory: ${err.message}`);
      return;
    }

    const groupedFiles: { [key: string]: string[] } = {};

    files.forEach((file) => {
      const baseName = file.replace(/(_\d+)?\.\w+$/, '');
      if (!groupedFiles[baseName]) {
        groupedFiles[baseName] = [];
      }
      groupedFiles[baseName].push(file);
    });

    for (const baseName in groupedFiles) {
      const folderPath = path.join(directoryPath, baseName);
      fs.mkdir(folderPath, { recursive: true }, (err) => {
        if (err) {
          console.error(`Error creating folder ${folderPath}: ${err.message}`);
          return;
        }

        groupedFiles[baseName].forEach((file) => {
          const oldPath = path.join(directoryPath, file);
          const newPath = path.join(folderPath, file);
          fs.rename(oldPath, newPath, (err) => {
            if (err) {
              console.error(`Error moving file ${file}: ${err.message}`);
            } else {
              console.log(`Moved ${file} to ${folderPath}`);
            }
          });
        });
      });
    }
  });
};

const directoryPath = process.argv[2];
if (!directoryPath) {
  console.error('Please provide a directory path.');
  process.exit(1);
}

organizeSprites(directoryPath);
