
<!-- @file   Doxyfile.in -->
<!-- @author Erik ZORZIN -->
<!-- @date   25OCT2019 -->
<!-- @brief  Instructions on how to use uncrustify. -->


This folder contains:
- the configuration file for uncrustify:
https://github.com/uncrustify/uncrustify

Uncrustify works fine in combination of the Atom editor:
https://atom.io

for which there is this plugin:
https://atom.io/packages/atom-beautify

These things together simplify the text editing by introducing a custom
indentation style and text formatting, described in the configuration file
present in this folder.

In order to work with this text style, do as follows:
1. install the Atom editor.
2. install the atom-beautify plugin.
3. install uncrustify.
4. copy the uncrustify.cfg file in a folder (e.g. in a hidden folder inside the
home directory: ~.uncrustify/uncrustify.cfg) and then install the "atom-beautify"
atom's plugin. Then configure the plugin (under the C++ section of its configuration)
to get the uncrustify from that path.

The atom-beautify plugin can be configured to beautify the code when saving it.
