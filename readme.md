# Registers

FANUC KAREL register and argument handling library. This library includes helper and utility functions for dealing with TP registers in a Karel program. [kl-registers](https://github.com/kobbled/kl-registers) also includes **src/registerstp.kl** which is a method of exposing karel variables & structs to TP/TP+ programs. see **include/registerstp.klh** for getters/setters.

The template, **lib/regmap.klc**, maps a karel struct to a set of TP registers, to expose karel struct to TP. See **test/config/testregmap.klt** for an example of configuring a regmap template.


>[!**NOTE**]
> if dealing with position registers use [kl-pose](https://github.com/kobbled/kl-pose). It includes setters and getters for `posreg_xyz`, and `posreg_joint`. For example a cart pose can be set with
>```ruby
> pose__set_posreg_xyz(POSE(0,0,100,0,0,0,(ZEROPOS(1).config_data)) <reg_no>, <grp_no>)
>```

## TP Interfaces

The current functions that can be called in TP+ are:

```ruby
intvar := R[2]
realvar := R[3]
strvar := SR[1]
posvar := PR[4]
jntvar := PR[5]
boolvar := R[4]

#getters
intvar = get_kint('<program_name>', '<karel_int_variable>')
realvar = get_krel('<program_name>', '<karel_real_variable>')
boolvar = get_kio('<program_name>', '<karel_bool_variable>', 'F')
strvar = get_kstr('<program_name>', '<karel_string_variable>')
posvar = get_kpos('<program_name>', '<karel_xyzwpr_variable>')
posvar.group(1) = get_kposgrp('<program_name>', '<karel_xyzwpr_variable>')
jntvar = get_kjnt('<program_name>', '<karel_jointpos_variable>')
jntvar.group(1) = get_kjntgrp('<program_name>', '<karel_jointpos_variable>')

#setters
set_kint(intvar, '<program_name>', '<karel_int_variable>')
set_krel(realvar, '<program_name>', '<karel_real_variable>')
set_kbool(boolvar, '<program_name>', '<karel_bool_variable>')
set_kstr(strvar, '<program_name>', '<karel_string_variable>')
set_kxyz(&posvar, '<program_name>', '<karel_xyzwpr_variable>')
set_kjnt(&jntvar, '<program_name>', '<karel_jointpos_variable>')
```

## tests

For library tests & usage see **test/test_regist.kl**

Run by building tests pushing and running kunit

```sh
rossum .. -w -o -t
ninja
kpush
kunit
```

TP+ program **test_set_var.tpp** is an example for setting karel variables from the teach pendant.

**test_regmap.kl** shows the tests for register mapping.

**test_set_struct.tpp** shows how to call a regmap object from TP+.

## regmap

A register map can be created by instancing this class in a karel file:

```c
%class tstrmp('regmap.klc','regmap.klh','<configuration-file>.klt')
```

The configuration file contains either `REGMAP_STRUCT` to define the struct in the regmap object, or `REGMAP_STRUCT_IMPORT` for importing an external struct. Then you have to declare both `REGMAPPGET`, and `REGMAPPSET`, to define the mapping between the struct, and the register set:

```c
%define REGMAPPGET `
  map_select_getter(progname, varname, 'SR', 1, 'str' , 'STRING')
  map_select_getter(progname, varname, 'R',  2, 'reg1', 'INTEGER')
  map_select_getter(progname, varname, 'R',  3, 'reg2', 'REAL')
  map_select_getter(progname, varname, 'PR', 4, 'pose', 'XYZWPR')
  map_select_getter(progname, varname, 'F',  1, 'io'  , 'BOOLEAN')
`

%define REGMAPPSET `
  map_select_setter(progname, varname, 'SR', 1, 'str' , 'STRING')
  map_select_setter(progname, varname, 'R',  2, 'reg1', 'INTEGER')
  map_select_setter(progname, varname, 'R',  3, 'reg2', 'REAL')
  map_select_setter(progname, varname, 'PR', 4, 'pose', 'XYZWPR')
  map_select_setter(progname, varname, 'F',  1, 'io'  , 'BOOLEAN')
`
```

Each line item refers to each member of the struct. The last 4 arguments need to be modified. Argument 3 is the register type to map the struct member to('R', 'PR', 'SR', 'F', 'DO', etc..). Argument 4 is the register number. argument 5 is the name of the member in the struct, and Argument 6 is the type of the struct member.
