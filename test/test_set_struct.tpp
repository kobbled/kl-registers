TP_GROUPMASK = "1,*,*,*,*"

.require :< "regmap.tpp"

intvar := R[2]
realvar := R[3]
strvar := SR[1]
posvar := PR[4]
boolvar := R[4]
flg    := F[5]

# get struct
# must run test_regmap test first
tstrmp(Regmap::SET,'test_regmap','out_struct')

