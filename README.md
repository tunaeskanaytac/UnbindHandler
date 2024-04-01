# UnbindHandler
A simple device unbinder using linux kernel's sysfs interface

## Installation
run:
```bash
make
```
## Usage
```bash
./unbind.out -l
```
list all the connected devices. Same as `cat /proc/bus/input/devices` command

```bash
./unbind.out -u <handler>
```
unbind the desired handler needs sudo privileges

### Example:
```bash
$> ./unbind.out -u js0

Please enter the index of the address you want to unbind
0: <random strings>
1: <random strings>
2: <random strings>
3: <random strings>
4: <random strings>
5: <address>
6: <random strings>

$> 5
unbind this: <address>
```
