# I2C-WiringX-Milk-V

This is source code to accompany my blog post: [Milk, I2C, and SMBus](https://satharus.me/tech/2024/08/27/i2c_milkv.html).

![example](extras/temperature.gif)

## How to: 
 - Follow the steps in the blog post to make sure you have a working musl RISC-V toolchain
 - Clone this repository: `git clone https://github.com/Satharus/I2C-WiringX-Milk-V`
 - Setup the environment: `source envsetup.sh`
 - Build the binary: `make`
 - Copy `sense` to the Milk-V Duo S
 - Run it: `./sense`
 - Profit??
