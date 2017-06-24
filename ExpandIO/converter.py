from bitstring import BitArray
with open('greta_vert.pbm','r') as f:
	for line in f:
		line = '0b' + line
		a = BitArray(line)
		print '0x'+ a.hex + ','