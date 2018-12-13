import csv
import math
import matplotlib.pyplot as plt
import numpy as np

def match(running_D, On_run_data, Off_run_list):
	D_min = 10e8
	Matced_Run = 0
	Del = 0
	matched_index = 0
	for idx, item_off in enumerate(Off_run_list):
		if(abs(float(On_run_data[5]) - float(item_off[5])) < 90):#Look for matched within +/- three months
			if(abs((float(On_run_data[1]) - float(item_off[1])) + running_D ) < abs(D_min)):
				if(On_run_data[0] != item_off[0] ):#Make sure on and off runs are different
					D_min = float(On_run_data[1]) - float(item_off[1]) + running_D
					Matced_Run = item_off[0]
					matched_index = idx	 
	return Matced_Run, D_min, matched_index

On_counts = []
Off_counts = []

#with open('Geminga.list') as on_list:
#with open('inputlist.list') as on_list:
with open('GemingaBest.list') as on_list:
	csv_reader = csv.reader(on_list, delimiter='\t')
        on_source_list_unsorted = list(csv_reader) 

with open('Crab.list') as off_list:
        csv_reader = csv.reader(off_list, delimiter='\t')
        off_source_list = list(csv_reader)

for off_item in off_source_list:
	print off_item
        Off_counts.append(float(off_item[1]))

for on_item in on_source_list_unsorted:
	print on_item
        On_counts.append(float(on_item[1]))

on_source_list = sorted(on_source_list_unsorted, key=lambda x: x[1])


running_D = 0
Matched_run = 0



while len(on_source_list) > 0:
	on_item = on_source_list.pop(len(on_source_list)-1)
	Matched_run,running_D, matched_run_i =  match(running_D, on_item, off_source_list)
	off_source_list.pop(matched_run_i)
	print on_item[0],'\t',Matched_run
	if(len(on_source_list)>0):
		on_item = on_source_list.pop(0)
		Matched_run,running_D,matched_run_i =  match(running_D, on_item, off_source_list)
		off_source_list.pop(matched_run_i)
		print on_item[0],'\t',Matched_run

#plt.figure(1) 
#a = np.hstack(On_counts)
#plt.hist(a, bins=10, range=[40000, 300000], color = 'blue')
#plt.title("On Run")

#plt.figure(2) 
#b = np.hstack(Off_counts)
#plt.hist(b, bins=10, range=[40000, 300000], color = 'red')
#plt.title("Off Run")

#plt.show()



