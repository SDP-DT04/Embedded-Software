# Embedded-Software

![alt text](https://assets-cdn.github.com/images/modules/logos_page/GitHub-Logo.png) <br /><br />

## Cloning and accessing repository into system

#### Clone repository (only have to do once)
```sh
$ git clone https://github.com/SDP-DT04/Embedded-Software
```

#### Change directory to cloned repository
```sh
$ cd Embedded-Software/
```

#### Checkout my personal branch
```sh
$ git checkout "branch-name"
```
Replace "branch-name" with the name of the branch you are trying to work on.

#### Commit changes to local version of repository
```sh
$ git commit
```

#### Push changes to the Github repository
```sh
$ git push origin "branch-name"
```
Replace "branch-name" with the name of the branch you are trying to work on. Type in credentials as requested.<br />

##Other useful information

#### Check to see if differences are online compared to local version
```sh
$ git diff
```

#### If differences and you want to include them then run
```sh
$ git checkout -A "branch-name"
```

#### Commit and Push individual files to branch rather than entire project
```sh
$ git commit "file".<extension>
$ git push origin "branch-name"
```
