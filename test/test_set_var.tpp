TP_GROUPMASK = "1,*,*,*,*"

intvar := R[2]
realvar := R[3]
strvar := SR[1]
posvar := PR[4]
boolvar := R[4]
flg    := F[1]

#initialize
intvar = 100
realvar = 2.718
strvar = Str::set('guten tag')
posvar.group(1) = Pos::setxyzgp(500, 500, 0, 90, 0, 180)
posvar.group(1) = Pos::setcfg('F U T, 0, 0, 0')
flg = on
boolvar = flg

# set struct in 'test_regmap'
set_kint(intvar, 'test_regmap', 'struct.reg1')
set_krel(realvar, 'test_regmap', 'struct.reg2')
set_kstr(strvar, 'test_regmap', 'struct.str')
set_kxyz(&posvar, 'test_regmap', 'struct.pose')
set_kbool(boolvar, 'test_regmap', 'struct.io')



