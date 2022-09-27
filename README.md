# Mario Kart Wii Tournament Museum

Source code for the MKWTM mod. Includes the rel source and the loader.

## Building

To compile code you'll need:

- NXP ['CodeWarrior Special Edition'][cw] for MPC55xx/MPC56xx v2.10
  - If this direct link doesn't work, the original page is
    ['available on the Internet Archive'][cwIA].
  - After installing it, you need `license.dat` from the installation root,
    and the DLL and EXE files inside `PowerPC_EABI_Tools/Command_Line_Tools`.
  - If you get a license error for `Win32_Plugins_Link_PPC`, add the
    following text to the end of the `license.dat` file:
    ```
    FEATURE Win32_Plugins_Link_PPC metrowks 8.0 permanent uncounted B08D7CC7D735 HOSTID=ANY
    ```
  - Useful documentation is in `Help/Power_Arch_Build_Tools_Reference.chm`
    (or `Help/PDF/Power Architecture Build Tools Reference.pdf`)

There is no real sophisticated build system for this project. To build as is, `PowerPC_EABI_Tools/Command_Line_Tools` must be in your `PATH` environment variable, then simply run `make`.

## Credits

### Tools

* [PistonMiner's elf2rel](https://github.com/PistonMiner/ttyd-tools/tree/master/ttyd-tools/elf2rel)

### Documentation and References

* [SeekyCt/mkw-structures](https://github.com/SeekyCt/mkw-structures)
* [riidefi/mkw](https://github.com/riidefi/mkw)

## License

All code under the src and loader directories are licensed under the MIT license. The full text of the license can be found in the 'LICENSE' file.


[cw]: http://cache.nxp.com/lgfiles/devsuites/PowerPC/CW55xx_v2_10_SE.exe?WT_TYPE=IDE%20-%20Debug,%20Compile%20and%20Build%20Tools&WT_VENDOR=FREESCALE&WT_FILE_FORMAT=exe&WT_ASSET=Downloads&fileExt=.exe
[cwIA]: http://web.archive.org/web/20160602205749/http://www.nxp.com/products/software-and-tools/software-development-tools/codewarrior-development-tools/downloads/special-edition-software:CW_SPECIALEDITIONS
