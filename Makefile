up:
	limactl create --name labsyouth ./lima-devm.yaml --debug
	limactl start labsyouth

down:
	limactl stop labsyouth

clean:
	limactl delete labsyouth -f

sh:
	limactl shell labsyouth
