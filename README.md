# FT_LS

ft_ls is an intermediate recreation of the ls command. The sorting for this project was done with binary trees, making it as efficient as system ls even on large input. `ls -laR /` for example! ft_ls is a systems project in the 42 curriculum.

## Getting Started

ft_ls uses [my 42 library](https://github.com/mint42/libft) which has been included as a git submodule. To set up this project, run `git clone https://github.com/mint42/ft_select` in the folder of your choice. Next, from the root of the repository run `git submodule update --init libft` to import the contents of the libft repository. Finally you can run `make` which will use the Makefile to build the library, and then the executable file `ft_ls`.

```
usage: ./ft_ls [-RTafglrt1] [file ...]
```

## Notes

- The `-g` flag is the flag for enabling colors, but typically this is `-G`. I did this because.
- This code does not compile on linux as of today.

## Author

[Ari Reedy](https://github.com/mint42/)
