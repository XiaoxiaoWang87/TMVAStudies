import sys
import os



input_dir = '/group/atlas/data/D3PDs/xwang/1LStopBoosted/plot_intput/20140727_DL/'
output_dir = '/group/atlas/data/D3PDs/xwang/1LStopBoosted/plot_output/20140727_DL/'

d = {}

d['Tt'] = ['Tt']
d['Wjets'] = ["W*BFilter*", "W*CJetFilter*", "W*CJetVetoBVeto*"]
d['Zjets'] = ["Z*BFilter*", "Z*CFilter*", "Z*CVetoBVeto*"]
d['singletop'] = ["singletop_tchan_l", "*_schan*", "*Wtchan*"]
d['ttbarV'] = ["ttbar*"]
d['topZ'] = ["tZ_*"]
d['Dibosons'] = ["WWtoenuqq_MassiveCB","WWtomunuqq_MassiveCB","WWtotaunuqq_MassiveCB","WZtoenuqq_MassiveCB","WZtomunuqq_MassiveCB","WZtotaunuqq_MassiveCB","ZWtoeeqq_MassiveCB","ZWtomumuqq_MassiveCB","ZWtotautauqq_MassiveCB","ZZtoeeqq_MassiveCB","ZZtomumuqq_MassiveCB","ZZtotautauqq_MassiveCB","lllnu_WZ_MassiveCB","llnunu_WW_MassiveCB","llnunu_ZZ_MassiveCB","lnununu_WZ_MassiveCB"]


d_tot = {}
d_tot['SM'] = ["Tt", "Wjets", "Zjets", "singletop", "ttbarV", "topZ", "Dibosons"]

#command0 = 'cd ' + input_dir
#os.system(command0)


for k, v in d.items():
    new = [s + '.root' for s in v]
    command = 'hadd ' + output_dir + k + '.root '
    for i in range(len(new)):
        command = command + input_dir + new[i] + ' '
    #print command
    os.system(command)

for k, v in d_tot.items():
    new = [s + '.root' for s in v]
    command = 'hadd ' + output_dir + k + '.root '
    for i in range(len(new)):
        command = command + output_dir + new[i] + ' '
    #print command
    os.system(command)
