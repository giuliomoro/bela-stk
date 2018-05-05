# STK on Bela

An example project to use [Bela](https://bela.io) with the [STK Synthesis Toolkit](https://github.com/thestk/stk).

## Prerequisites:

Install STK. This can be done with `apt-get install libstk`, or by cloning the [STK source code](https://github.com/thestk/stk) on your Bela board and running, from within the `stk` folder:

```
./configure && make && make install && ldconfig
```

## Usage:

### With the Bela IDE

* Open the Bela IDE, create a new C++ project, drag and drop the files from this repo in the project.
* Hit run.
* Enjoy the STK sinewaves.

#### Under the hood

The options specified in `settings.json` (which are visualized in the IDE's project settings) pass to `make` the option `LDLIBS=-lstk` which tells the linker to link to `libstk`.

### From the command line

Just build a regular Bela project and link to `libstk`:
```
make -C ~/Bela PROJECT=bela-stk LDLIBS=-lstk run
```

## More fun

This project is based on the example in `stk/proects/examples/sine.cpp`, but instead of writing the output to a file, it writes it to the Bela audio output. Look for other examples in that folder to have more fun with STK and learn how to use it. Also, refer to the STK docs for more details.

