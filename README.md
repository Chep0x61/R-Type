# Setup Project
```bash
mkdir build
```

### Then

```bash
./configure.sh
```

### Or

```bash
python3 -m pip install -r requirements.txt
```
```bash
cmake . -B build -D CMAKE_BUILD_TYPE=Debug
```
```bash
make -C build -j{number_of_threads}
```

# Workflow

## Before a feature development
Before a feature development, I assign myself to the Github Issue and I create a branch (from master) with naming convention (RT-{issue-number}-{short description of issue})
Example: RT-32-create_user

## Before a commit
- I verify the coding style with the ci_test target
```bash
make ci_test
```
- I name my commit with less than 50 characters

## I have finished my feature work
- I commit my work with following convention : ([ticket-id][feature/fix] milestone: description)          Example : [issue-36][fix] network: fix tcp socket
- I create a pull request on Github on the dev branch
- I assign the review to Florian Kamps

# Documentations

## Network RFC

####  [Click to open the network doc](https://github.com/Chep0x61/R-Type/blob/main/doc/network_rfc.pdf)

## Project Documentation

####  [Click to open the project doc](https://github.com/Chep0x61/R-Type/blob/main/doc/refman.pdf)

# Our Team

### Developers

| [<img src="https://github.com/flokamps.png?size=85" width=85><br><sub>Flokamps</sub>](https://github.com/flokamps) | [<img src="https://github.com/AlexandreCoyras.png?size=85" width=85><br><sub>Alexandre Coyras</sub>](https://github.com/AlexandreCoyras) | [<img src="https://github.com/Naikyz.png?size=85" width=85><br><sub>Naikyz</sub>](https://github.com/Naikyz) | [<img src="https://github.com/Lolo-Mytsu.png?size=85" width=85><br><sub>Loïs Aibout</sub>](https://github.com/Lolo-Mytsu)  | [<img src="https://github.com/Chep0x61.png?size=85" width=85><br><sub>Chep0x61</sub>](https://github.com/Chep0x61)
| :---: | :---: | :---: | :---: | :---:

### Content Creators

| [<img src=".github/assets/PRacon.jpg" width=85><br><sub>Philippe Racon</sub>](https://soundcloud.com/user-736943015) | [<img src=".github/assets/ACharleville.jpg" width=85><br><sub>Alizée Charleville</sub>](https://linktr.ee/Charleville)
| :---: | :---:

#### :heart: Special thanks to Philippe Racon "Fyra" & Alizée Charleville for their awesome skills in music and sound effects. You can find them on their link just above. :heart:

#### We hope this ReadMe was useful ! :heart:
