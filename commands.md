If you want to replace the default chess spritesheet, you can relace the existing one by converting yours using this command :
```sh
${N64_INST}/bin/mksprite --verbose --format RGBA16 --compress 0 ./sprite.png
```

The rom can be uploaded on a flashcard with this command (-d only required for debug console) :
```sh
UNFLoader -r ./hello.z64 -d
```
