Pong - Game Boy
============

![Vídeo sem título (1)](https://user-images.githubusercontent.com/1587926/224572246-b3a9e818-8653-4646-b93b-1d5fd7891058.gif)

Pong game for Gameboy, written with GBDK

# Compiling

If you have GBDK (`with GBDKDIR env defined`) and CMake already installed. You only need to run those commands:

```bash
$ cmake -Bbuild -H.
$ cmake --build build
```

### Docker

Compiling the project using docker

```bash
$ docker run -v $PWD/:/app -w /app caiotava/gameboy-dev sh -c "cmake -Bbuild -H. && cmake --build build"
```


## Credits

Text font and Sounds - https://laroldsjubilantjunkyard.com/