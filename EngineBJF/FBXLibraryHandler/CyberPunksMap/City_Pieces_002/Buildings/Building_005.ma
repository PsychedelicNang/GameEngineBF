//Maya ASCII 2015 scene
//Name: Building_005.ma
//Last modified: Mon, Mar 26, 2018 01:07:16 PM
//Codeset: 1252
requires maya "2015";
currentUnit -l centimeter -a degree -t ntsc;
fileInfo "application" "maya";
fileInfo "product" "Maya 2015";
fileInfo "version" "2015";
fileInfo "cutIdentifier" "201405190330-916664";
fileInfo "osv" "Microsoft Windows 7 Business Edition, 64-bit Windows 7 Service Pack 1 (Build 7601)\n";
fileInfo "license" "student";
createNode transform -s -n "persp";
	setAttr ".t" -type "double3" -1112.3612114192065 4360.889836958966 -14092.398488606608 ;
	setAttr ".r" -type "double3" -9.3383527346177289 2346.2000000004855 0 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v";
	setAttr ".fl" 34.999999999999993;
	setAttr ".fcp" 1000000;
	setAttr ".coi" 15738.291885079801;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" 564.8382568359375 1807.1258538961411 1346.4849853515625 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".t" -type "double3" 2386.8811650659486 25577.720745569954 4483.6409692783309 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".fcp" 1000000;
	setAttr ".coi" 16473.261013283962;
	setAttr ".ow" 4310.5585740529814;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".t" -type "double3" 624.83366722363371 165.48332316223554 5437.9160128694366 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".coi" 5435.9476562500004;
	setAttr ".ow" 1586.7485742956449;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".t" -type "double3" 5578.9988705020405 115.28067534251929 -140.68030302150328 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v";
	setAttr ".rnd" no;
	setAttr ".coi" 5435.9476562500004;
	setAttr ".ow" 1583.5900573039542;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "Building_005";
	setAttr ".rp" -type "double3" 3732.0379638671875 1100.9309082031277 4772.03564453125 ;
	setAttr ".sp" -type "double3" 3732.0379638671875 1100.9309082031277 4772.03564453125 ;
createNode mesh -n "Building_005Shape" -p "Building_005";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 225 ".uvst[0].uvsp[0:224]" -type "float2" 0.50599998 0.75379997
		 0.99669999 0.75669998 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997
		 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998
		 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999
		 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997
		 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908
		 0.50599998 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998
		 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998
		 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999
		 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999
		 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999
		 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999 1.0020999908
		 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997
		 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998
		 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999
		 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997
		 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908
		 0.50599998 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998
		 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998
		 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999
		 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997 0.56870002 0.1195 0.56870002
		 0.0031000001 0.68080002 0.0031000001 0.68080002 0.1195 0.50599998 0.75379997 0.99669999
		 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999
		 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999 1.0020999908
		 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997
		 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998
		 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999
		 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998 0.75379997
		 0.50599998 0.75379997 0.99669999 0.75669998 0.99669999 1.0020999908 0.99669999 1.0020999908
		 0.50599998 0.99919999 0.50599998 0.75379997 0.50599998 0.75379997 0.99669999 0.75669998
		 0.99669999 1.0020999908 0.99669999 1.0020999908 0.50599998 0.99919999 0.50599998
		 0.75379997 0.39559999 0.47729999 0.26300001 0.43630001 0.26300001 0.3037 0.47760001
		 0.37 0.39559999 0.26269999 1 1.0029000044 0.50160003 0.99870002 0.59719998 0.94270003
		 0.90259999 0.94679999 0.50160003 0.75620002 0.59719998 0.75620002 0.49869999 0.9971
		 0.49869999 0.75470001 0.59429997 0.75470001 0.59429997 0.9971 0.50010002 0.99699998
		 0.50010002 0.75459999 0.59570003 0.81059998 0.59570003 0.99699998 0.99860001 0.75440001
		 0.90109998 0.81040001 0.99860001 1.0011999607 0.90109998 1.0011999607 0.9971 0.75880003
		 0.9971 1.0012999773 0.89969999 1.0012999773 0.89969999 0.75880003 1 0.7604 0.90259999
		 0.7604 0.49939999 0.1195 0.49939999 0.0031000001 0.99360001 0.0040000002 0.92110002
		 0.0040000002 0.95160002 0.1207 0.82679999 0.0040000002 0.7543 0.0040000002 0.79689997
		 0.1207 0.74989998 0.0031000001 0.74989998 0.1195 0.7543 0.0040000002 0.82679999 0.0040000002
		 0.95160002 0.1207 0.95160002 0.1207 0.79689997 0.1207 0.7543 0.0040000002 0.82679999
		 0.0040000002 0.92110002 0.0040000002 0.95160002 0.1207 0.92110002 0.0040000002 0.99360001
		 0.0040000002 0.95160002 0.1207 0.56879997 0.003 0.56879997 0.1194 0.68080002 0.1196
		 0.68080002 0.0031000001 0.50190002 0.99870002 1.00030004978 1.0029000044 0.90270001
		 0.94679999 0.59789997 0.94270003 1.00030004978 0.7604 0.90270001 0.7604 0.99739999
		 1.0012999773 0.99739999 0.75880003 0.8998 0.75880003 0.8998 1.0012999773 0.9989 1.0011999607
		 0.9989 0.75440001 0.9012 0.81040001 0.9012 1.0011999607 0.50040001 0.75459999 0.59640002
		 0.81059998 0.50040001 0.99699998 0.59640002 0.99699998 0.49900001 0.75470001 0.49900001
		 0.9971 0.59500003 0.9971 0.59500003 0.75470001 0.50190002 0.75620002 0.59789997 0.75620002
		 0.49939999 0.0031000001 0.49939999 0.1195 0.49939999 0.0031000001 0.99360001 0.0040000002
		 0.92110002 0.0040000002 0.9515 0.1207 0.92110002 0.0040000002 0.82679999 0.0040000002
		 0.82679999 0.0040000002 0.7543 0.0040000002 0.79689997 0.1207 0.79689997 0.1207 0.82679999
		 0.0040000002 0.74989998 0.1195 0.74989998 0.0031000001 0.68080002 0.0031000001 0.68080002
		 0.0031000001 0.74989998 0.1195 0.7543 0.0040000002 0.82679999 0.0040000002 0.9515
		 0.1207 0.9515 0.1207 0.79689997 0.1207 0.7543 0.0040000002 0.82679999 0.0040000002
		 0.92110002 0.0040000002 0.9515 0.1207 0.92110002 0.0040000002 0.99360001 0.0040000002
		 0.9515 0.1207;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr -s 54 ".vt[0:53]"  3855.068603516 5.4569682e-012 4071.16381836
		 3158.79321289 5.4569682e-012 4163.80859375 3158.79321289 440.37265015 4163.80859375
		 3855.068603516 440.37265015 4071.16381836 3031.7434082 5.4569682e-012 4854.63623047
		 3031.7434082 440.37265015 4854.63623047 3649.49804688 5.4569682e-012 5188.94433594
		 3649.49804688 440.37265015 5188.94433594 4158.34179688 5.4569682e-012 4704.73144531
		 4158.34179688 440.37265015 4704.73144531 3158.79321289 880.74499512 4163.80859375
		 3855.068603516 880.74499512 4071.16381836 3031.7434082 880.74499512 4854.63623047
		 4158.34179688 880.74499512 4704.73144531 3649.49804688 880.74499512 5188.94433594
		 3158.79321289 1321.11767578 4163.80859375 3855.068603516 1321.11767578 4071.16381836
		 3031.7434082 1321.11767578 4854.63623047 4158.34179688 1321.11767578 4704.73144531
		 3649.49804688 1321.11767578 5188.94433594 3158.79321289 1761.49060059 4163.80859375
		 3855.068603516 1761.49060059 4071.16381836 3031.7434082 1761.49060059 4854.63623047
		 2917.30541992 739.85369873 5356.15136719 3292.2409668 739.85369873 5559.053710938
		 3292.2409668 1462.0089111328 5559.053710938 2917.30541992 1462.0089111328 5356.15136719
		 4158.34179688 1761.49060059 4704.73144531 3649.49804688 1761.49060059 5188.94433594
		 3158.79321289 2201.86181641 4163.80859375 3855.068603516 2201.86181641 4071.16381836
		 3031.7434082 2201.86181641 4854.63623047 3649.49804688 2201.86181641 5188.94433594
		 4158.34179688 2201.86181641 4704.73144531 3528.088378906 542.11566162 5123.24169922
		 3153.15283203 542.11566162 4920.33886719 3528.088378906 880.74499512 5123.24169922
		 3528.088378906 1321.11767578 5123.24169922 3528.088378906 1659.74621582 5123.24169922
		 3153.15283203 1659.74621582 4920.33886719 3153.15283203 1321.11767578 4920.33886719
		 3153.15283203 880.74499512 4920.33886719 4546.77050781 739.85369873 4370.016113281
		 4363.68017578 739.85369873 3985.017578125 4363.68017578 1462.0089111328 3985.017578125
		 4546.77050781 1462.0089111328 4370.016113281 3916.16894531 542.11566162 4197.8359375
		 4099.25927734 542.11566162 4582.83349609 3916.16894531 880.74499512 4197.8359375
		 3916.16894531 1321.11767578 4197.8359375 3916.16894531 1659.74621582 4197.8359375
		 4099.25927734 1659.74621582 4582.83349609 4099.25927734 1321.11767578 4582.83349609
		 4099.25927734 880.74499512 4582.83349609;
	setAttr -s 154 ".ed[0:153]"  0 1 0 1 2 0 2 3 0 3 0 0 1 4 0 4 5 0 5 1 0
		 5 2 0 4 6 0 6 7 0 7 4 0 7 5 0 6 8 0 8 9 0 9 6 0 9 7 0 8 0 0 3 8 0 3 9 0 2 10 0 10 3 0
		 10 11 0 11 3 0 5 12 0 12 2 0 12 10 0 9 13 0 13 7 0 13 14 0 14 7 0 10 15 0 15 11 0
		 15 16 0 16 11 0 12 17 0 17 10 0 17 15 0 13 18 0 18 14 0 18 19 0 19 14 0 15 20 0 20 16 0
		 20 21 0 21 16 0 17 22 0 22 15 0 22 20 0 23 24 0 24 25 0 25 26 0 26 23 0 18 27 0 27 19 0
		 27 28 0 28 19 0 20 29 0 29 21 0 29 30 0 30 21 0 22 31 0 31 20 0 31 29 0 22 28 0 28 32 0
		 32 22 0 32 31 0 27 33 0 33 28 0 33 32 0 27 21 0 30 27 0 30 33 0 32 29 0 32 30 0 7 34 0
		 34 5 0 34 35 0 35 5 0 14 36 0 36 7 0 36 34 0 19 37 0 37 14 0 37 36 0 28 38 0 38 19 0
		 38 37 0 22 39 0 39 28 0 39 38 0 17 40 0 40 22 0 40 39 0 12 41 0 41 17 0 41 40 0 35 12 0
		 35 41 0 34 24 0 24 35 0 23 35 0 36 24 0 37 24 0 38 25 0 25 37 0 39 26 0 26 38 0 40 23 0
		 23 39 0 41 23 0 42 43 0 43 44 0 44 45 0 45 42 0 3 46 0 46 9 0 46 47 0 47 9 0 11 48 0
		 48 3 0 48 46 0 16 49 0 49 11 0 49 48 0 21 50 0 50 16 0 50 49 0 27 51 0 51 21 0 51 50 0
		 18 52 0 52 27 0 52 51 0 13 53 0 53 18 0 53 52 0 47 13 0 47 53 0 46 43 0 43 47 0 42 47 0
		 48 43 0 49 43 0 50 44 0 44 49 0 51 45 0 45 50 0 52 42 0 42 51 0 53 42 0 1 3 1 24 26 1
		 43 45 1;
	setAttr -s 297 ".n";
	setAttr ".n[0:165]" -type "float3"  -0.0005607839 0 -0.0042138426 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.0020232331
		 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331
		 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0038343915
		 0 -0.0018353177 0.0038343915 0 -0.0018353177 0.0038343915 0 -0.0018353177 0.0038343915
		 0 -0.0018353177 0.0038343915 0 -0.0018353177 0.0038343915 0 -0.0018353177 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.0020232331
		 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331
		 0 0.0037386466 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427
		 0 0.0030794288 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839
		 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839 0 -0.0042138426 -0.0005607839
		 0 -0.0042138426 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856
		 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856 0 -0.00076902763 -0.004180856
		 0 -0.00076902763 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331
		 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331
		 0 0.0037386466 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427
		 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427 0 0.0030794288 0.0029305427
		 0 0.0030794288 0.0038343915 0 -0.0018353177 0.0038343915 0 -0.0018353177 0.0038343915
		 0 -0.0018353177 0.0038343915 0 -0.0018353177 0.0038343915 0 -0.0018353177 0.0038343915
		 0 -0.0018353177 0 0.0057678442 0 0 0.0057678442 0 0 0.0057678442 0 0 0.0057678442
		 0 0 0.0057678442 0 0 0.0057678442 0 0 0.0057678442 0 0 0.0057678442 0 0 0.0057678442
		 0 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466
		 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466;
	setAttr ".n[166:296]" -type "float3"  -0.0020232331 0 0.0037386466 -0.0020232331
		 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331
		 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0020232331 0 0.0037386466 -0.0009632532
		 -0.0050722016 0.0017799548 -0.0009632532 -0.0050722016 0.0017799548 -0.0009632532
		 -0.0050722016 0.0017799548 -0.0009632532 -0.0050722016 0.0017799548 -0.0009632532
		 -0.0050722016 0.0017799548 -0.0009632532 -0.0050722016 0.0017799548 0.0037386464
		 0 0.0020232331 0.0037386464 0 0.0020232331 0.0037386464 0 0.0020232331 0.0037386464
		 0 0.0020232331 0.0037386464 0 0.0020232331 0.0037386464 0 0.0020232331 0.0037386464
		 0 0.0020232331 0.0037386464 0 0.0020232331 0.0037386464 0 0.0020232331 0.0037386464
		 0 0.0020232331 0.0037386464 0 0.0020232331 0.0037386464 0 0.0020232331 -0.0009632532
		 0.0050722016 0.0017799548 -0.0009632532 0.0050722016 0.0017799548 -0.0009632532 0.0050722016
		 0.0017799548 -0.0009632532 0.0050722016 0.0017799548 -0.0009632532 0.0050722016 0.0017799548
		 -0.0009632532 0.0050722016 0.0017799548 -0.0037386464 0 -0.0020232331 -0.0037386464
		 0 -0.0020232331 -0.0037386464 0 -0.0020232331 -0.0037386464 0 -0.0020232331 -0.0037386464
		 0 -0.0020232331 -0.0037386464 0 -0.0020232331 -0.0037386464 0 -0.0020232331 -0.0037386464
		 0 -0.0020232331 -0.0037386464 0 -0.0020232331 -0.0037386464 0 -0.0020232331 -0.0037386464
		 0 -0.0020232331 -0.0037386464 0 -0.0020232331 0.0038389652 0 -0.0018257273 0.0038389652
		 0 -0.0018257273 0.0038389652 0 -0.0018257273 0.0038389652 0 -0.0018257273 0.0038343742
		 -1.7303533e-005 -0.0018353126 0.0038343742 -1.7303533e-005 -0.0018353126 0.0038343742
		 -1.7303533e-005 -0.0018353126 0.0038388665 4.2105265e-005 -0.001825679 0.0038388665
		 4.2105265e-005 -0.001825679 0.0038388665 4.2105265e-005 -0.001825679 0.0038288711
		 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711
		 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711
		 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711
		 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711
		 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711
		 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038288711 0 -0.0018468122 0.0038343468
		 -2.7685654e-005 -0.0018352981 0.0038343468 -2.7685654e-005 -0.0018352981 0.0038343468
		 -2.7685654e-005 -0.0018352981 0.003838907 3.2299926e-005 -0.0018257006 0.003838907
		 3.2299926e-005 -0.0018257006 0.003838907 3.2299926e-005 -0.0018257006 0.0038252769
		 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769
		 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769
		 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769
		 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769
		 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769
		 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0038252769 0 -0.0018542381 0.0018277143
		 -0.0050721555 -0.00086937344 0.0018277143 -0.0050721555 -0.00086937344 0.0018277143
		 -0.0050721555 -0.00086937344 0.0018277143 -0.0050721555 -0.00086937344 0.0018277143
		 -0.0050721555 -0.00086937344 0.0018277143 -0.0050721555 -0.00086937344 -0.0018257271
		 0 -0.0038389652 -0.0018257271 0 -0.0038389652 -0.0018257271 0 -0.0038389652 -0.0018257271
		 0 -0.0038389652 -0.0018257271 0 -0.0038389652 -0.0018257271 0 -0.0038389652 -0.0018257271
		 0 -0.0038389652 -0.0018257271 0 -0.0038389652 -0.0018257271 0 -0.0038389652 -0.0018257271
		 0 -0.0038389652 -0.0018257271 0 -0.0038389652 -0.0018257271 0 -0.0038389652 0.0018277143
		 0.0050721555 -0.00086937344 0.0018277143 0.0050721555 -0.00086937344 0.0018277143
		 0.0050721555 -0.00086937344 0.0018277143 0.0050721555 -0.00086937344 0.0018277143
		 0.0050721555 -0.00086937344 0.0018277143 0.0050721555 -0.00086937344 0.0018257271
		 0 0.0038389652 0.0018257271 0 0.0038389652 0.0018257271 0 0.0038389652 0.0018257271
		 0 0.0038389652 0.0018257271 0 0.0038389652 0.0018257271 0 0.0038389652 0.0018257271
		 0 0.0038389652 0.0018257271 0 0.0038389652 0.0018257271 0 0.0038389652 0.0018257271
		 0 0.0038389652 0.0018257271 0 0.0038389652 0.0018257271 0 0.0038389652;
	setAttr -s 101 -ch 303 ".fc[0:100]" -type "polyFaces" 
		f 3 0 151 3
		mu 0 3 0 1 3
		f 3 -152 1 2
		mu 0 3 3 1 2
		f 3 4 5 6
		mu 0 3 4 5 6
		f 3 7 -2 -7
		mu 0 3 7 8 9
		f 3 8 9 10
		mu 0 3 10 11 12
		f 3 11 -6 -11
		mu 0 3 13 14 15
		f 3 12 13 14
		mu 0 3 16 17 18
		f 3 15 -10 -15
		mu 0 3 19 20 21
		f 3 16 -4 17
		mu 0 3 22 23 24
		f 3 18 -14 -18
		mu 0 3 25 26 27
		f 3 -3 19 20
		mu 0 3 28 29 30
		f 3 21 22 -21
		mu 0 3 31 32 33
		f 3 -8 23 24
		mu 0 3 34 35 36
		f 3 25 -20 -25
		mu 0 3 37 38 39
		f 3 -16 26 27
		mu 0 3 40 41 42
		f 3 28 29 -28
		mu 0 3 43 44 45
		f 3 -22 30 31
		mu 0 3 46 47 48
		f 3 32 33 -32
		mu 0 3 49 50 51
		f 3 -26 34 35
		mu 0 3 52 53 54
		f 3 36 -31 -36
		mu 0 3 55 56 57
		f 3 -29 37 38
		mu 0 3 58 59 60
		f 3 39 40 -39
		mu 0 3 61 62 63
		f 3 -33 41 42
		mu 0 3 64 65 66
		f 3 43 44 -43
		mu 0 3 67 68 69
		f 3 -37 45 46
		mu 0 3 70 71 72
		f 3 47 -42 -47
		mu 0 3 73 74 75
		f 3 48 152 51
		mu 0 3 76 77 79
		f 3 -153 49 50
		mu 0 3 79 77 78
		f 3 -40 52 53
		mu 0 3 80 81 82
		f 3 54 55 -54
		mu 0 3 83 84 85
		f 3 -44 56 57
		mu 0 3 86 87 88
		f 3 58 59 -58
		mu 0 3 89 90 91
		f 3 -48 60 61
		mu 0 3 92 93 94
		f 3 62 -57 -62
		mu 0 3 95 96 97
		f 3 63 64 65
		mu 0 3 98 99 100
		f 3 66 -61 -66
		mu 0 3 101 102 103
		f 3 -55 67 68
		mu 0 3 104 105 106
		f 3 69 -65 -69
		mu 0 3 107 108 109
		f 3 70 -60 71
		mu 0 3 110 111 112
		f 3 72 -68 -72
		mu 0 3 113 114 115
		f 3 -63 -67 73
		mu 0 3 116 117 118
		f 3 -59 -74 74
		mu 0 3 119 116 118
		f 3 -73 -75 -70
		mu 0 3 120 119 118
		f 3 -12 75 76
		mu 0 3 121 122 123
		f 3 77 78 -77
		mu 0 3 123 124 121
		f 3 -30 79 80
		mu 0 3 122 125 126
		f 3 81 -76 -81
		mu 0 3 126 123 122
		f 3 -41 82 83
		mu 0 3 127 128 129
		f 3 84 -80 -84
		mu 0 3 129 130 127
		f 3 -56 85 86
		mu 0 3 131 132 133
		f 3 87 -83 -87
		mu 0 3 133 134 131
		f 3 -64 88 89
		mu 0 3 132 135 136
		f 3 90 -86 -90
		mu 0 3 136 133 132
		f 3 -46 91 92
		mu 0 3 135 137 138
		f 3 93 -89 -93
		mu 0 3 138 136 135
		f 3 -35 94 95
		mu 0 3 139 140 141
		f 3 96 -92 -96
		mu 0 3 141 142 139
		f 3 -24 -79 97
		mu 0 3 143 121 124
		f 3 98 -95 -98
		mu 0 3 124 144 143
		f 3 -78 99 100
		mu 0 3 145 146 77
		f 3 -49 101 -101
		mu 0 3 77 76 145
		f 3 -82 102 -100
		mu 0 3 147 148 149
		f 3 -85 103 -103
		mu 0 3 148 150 149
		f 3 -88 104 105
		mu 0 3 150 151 152
		f 3 -50 -104 -106
		mu 0 3 152 149 150
		f 3 -91 106 107
		mu 0 3 153 154 79
		f 3 -51 -105 -108
		mu 0 3 79 78 153
		f 3 -94 108 109
		mu 0 3 155 156 157
		f 3 -52 -107 -110
		mu 0 3 158 159 160
		f 3 -97 110 -109
		mu 0 3 161 162 163
		f 3 -99 -102 -111
		mu 0 3 164 165 166
		f 3 111 153 114
		mu 0 3 167 168 170
		f 3 -154 112 113
		mu 0 3 170 168 169
		f 3 -19 115 116
		mu 0 3 171 172 173
		f 3 117 118 -117
		mu 0 3 173 174 171
		f 3 -23 119 120
		mu 0 3 172 175 176
		f 3 121 -116 -121
		mu 0 3 176 173 172
		f 3 -34 122 123
		mu 0 3 177 178 179
		f 3 124 -120 -124
		mu 0 3 179 180 177
		f 3 -45 125 126
		mu 0 3 181 182 183
		f 3 127 -123 -127
		mu 0 3 183 184 181
		f 3 -71 128 129
		mu 0 3 182 185 186
		f 3 130 -126 -130
		mu 0 3 186 183 182
		f 3 -53 131 132
		mu 0 3 185 187 188
		f 3 133 -129 -133
		mu 0 3 188 186 185
		f 3 -38 134 135
		mu 0 3 189 190 191
		f 3 136 -132 -136
		mu 0 3 191 192 189
		f 3 -27 -119 137
		mu 0 3 193 171 174
		f 3 138 -135 -138
		mu 0 3 174 194 193
		f 3 -118 139 140
		mu 0 3 195 196 168
		f 3 -112 141 -141
		mu 0 3 168 167 197
		f 3 -122 142 -140
		mu 0 3 198 199 200
		f 3 -125 143 -143
		mu 0 3 201 202 200
		f 3 -128 144 145
		mu 0 3 203 204 205
		f 3 -113 -144 -146
		mu 0 3 206 200 207
		f 3 -131 146 147
		mu 0 3 208 209 210
		f 3 -114 -145 -148
		mu 0 3 211 169 212
		f 3 -134 148 149
		mu 0 3 213 214 215
		f 3 -115 -147 -150
		mu 0 3 216 217 218
		f 3 -137 150 -149
		mu 0 3 219 220 221
		f 3 -139 -142 -151
		mu 0 3 222 223 224;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
createNode shadingEngine -n "SciFi_CharacterSG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
createNode lambert -n "SciFi_CharacterSG1";
	setAttr ".c" -type "float3" 0 0 0 ;
createNode shadingEngine -n "Alleyway01SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
createNode lambert -n "Alleyway01SG1";
createNode lightLinker -s -n "lightLinker1";
	setAttr -s 7 ".lnk";
	setAttr -s 7 ".slnk";
createNode displayLayerManager -n "layerManager";
	setAttr ".cdl" 8;
	setAttr -s 11 ".dli[1:10]"  1 7 3 4 5 2 6 8 
		9 10;
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
createNode lambert -n "lambert2";
createNode shadingEngine -n "lambert2SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo3";
createNode file -n "file1";
	setAttr ".ftn" -type "string" "D:/Full Sail/New Library/Checked/3D/6. Buildings/Alien Buildings/alienbuildings.png";
createNode place2dTexture -n "place2dTexture1";
createNode script -n "uiConfigurationScriptNode";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n"
		+ "                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n"
		+ "                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n"
		+ "                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n"
		+ "            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n"
		+ "            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n"
		+ "            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n"
		+ "                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n"
		+ "                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n"
		+ "                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n"
		+ "        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n"
		+ "            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n"
		+ "            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n"
		+ "                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n"
		+ "                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n"
		+ "                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n"
		+ "            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n"
		+ "            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n"
		+ "                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n"
		+ "                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 0\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n"
		+ "\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n"
		+ "            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n"
		+ "            -lights 1\n            -cameras 0\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n                -docTag \"isolOutln_fromSeln\" \n                -showShapes 0\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 1\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n"
		+ "                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 0\n                -ignoreHiddenAttribute 0\n"
		+ "                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n"
		+ "            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\toutlinerPanel -e -to $panelName;\n"
		+ "\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n"
		+ "                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n"
		+ "                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1.25\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n"
		+ "                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n"
		+ "                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n"
		+ "                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1.25\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n"
		+ "                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n"
		+ "                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n"
		+ "                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n"
		+ "                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n"
		+ "                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n"
		+ "                -manageSequencer 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"sequenceEditorPanel\" -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n"
		+ "                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n"
		+ "                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n"
		+ "\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n"
		+ "                -extendToShapes 1\n                $editorName;;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n"
		+ "                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"createNodePanel\" -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 0\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 0\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 1 -size 10 -divisions 10 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	setAttr ".b" -type "string" "playbackOptions -min 0 -max 100 -ast 0 -aet 100 ";
	setAttr ".st" 6;
createNode phong -n "blinn1";
	setAttr ".cp" 6.311790943145752;
createNode shadingEngine -n "pCube1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo4";
createNode file -n "file3";
	setAttr ".ftn" -type "string" "D:/Full Sail/Art Fixes/Our Team/level/Barrier_Concrete/Barrier.fbm/TEX_Barrier1_D.png";
createNode place2dTexture -n "place2dTexture2";
createNode lambert -n "lambert3";
createNode shadingEngine -n "lambert3SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo5";
createNode file -n "file4";
	setAttr ".ftn" -type "string" "D:/Full Sail/Art Fixes/Our Team/level/Ground.jpg";
createNode place2dTexture -n "place2dTexture3";
select -ne :time1;
	setAttr ".o" 0;
select -ne :renderPartition;
	setAttr -s 7 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 7 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 3 ".u";
select -ne :defaultRenderingList1;
select -ne :defaultTextureList1;
	setAttr -s 3 ".tx";
connectAttr "SciFi_CharacterSG1.oc" "SciFi_CharacterSG.ss";
connectAttr "SciFi_CharacterSG.msg" "materialInfo1.sg";
connectAttr "SciFi_CharacterSG1.msg" "materialInfo1.m";
connectAttr "Alleyway01SG1.oc" "Alleyway01SG.ss";
connectAttr "Alleyway01SG.msg" "materialInfo2.sg";
connectAttr "Alleyway01SG1.msg" "materialInfo2.m";
relationship "link" ":lightLinker1" "SciFi_CharacterSG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Alleyway01SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "lambert2SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "pCube1SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "lambert3SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "SciFi_CharacterSG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Alleyway01SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "lambert2SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "pCube1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "lambert3SG.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "file1.oc" "lambert2.c";
connectAttr "lambert2.oc" "lambert2SG.ss";
connectAttr "Building_005Shape.iog" "lambert2SG.dsm" -na;
connectAttr "lambert2SG.msg" "materialInfo3.sg";
connectAttr "lambert2.msg" "materialInfo3.m";
connectAttr "file1.msg" "materialInfo3.t" -na;
connectAttr "place2dTexture1.c" "file1.c";
connectAttr "place2dTexture1.tf" "file1.tf";
connectAttr "place2dTexture1.rf" "file1.rf";
connectAttr "place2dTexture1.mu" "file1.mu";
connectAttr "place2dTexture1.mv" "file1.mv";
connectAttr "place2dTexture1.s" "file1.s";
connectAttr "place2dTexture1.wu" "file1.wu";
connectAttr "place2dTexture1.wv" "file1.wv";
connectAttr "place2dTexture1.re" "file1.re";
connectAttr "place2dTexture1.of" "file1.of";
connectAttr "place2dTexture1.r" "file1.ro";
connectAttr "place2dTexture1.n" "file1.n";
connectAttr "place2dTexture1.vt1" "file1.vt1";
connectAttr "place2dTexture1.vt2" "file1.vt2";
connectAttr "place2dTexture1.vt3" "file1.vt3";
connectAttr "place2dTexture1.vc1" "file1.vc1";
connectAttr "place2dTexture1.o" "file1.uv";
connectAttr "place2dTexture1.ofs" "file1.fs";
connectAttr "file3.oc" "blinn1.c";
connectAttr "blinn1.oc" "pCube1SG.ss";
connectAttr "pCube1SG.msg" "materialInfo4.sg";
connectAttr "blinn1.msg" "materialInfo4.m";
connectAttr "file3.msg" "materialInfo4.t" -na;
connectAttr "place2dTexture2.o" "file3.uv";
connectAttr "place2dTexture2.ofu" "file3.ofu";
connectAttr "place2dTexture2.ofv" "file3.ofv";
connectAttr "place2dTexture2.rf" "file3.rf";
connectAttr "place2dTexture2.reu" "file3.reu";
connectAttr "place2dTexture2.rev" "file3.rev";
connectAttr "place2dTexture2.vt1" "file3.vt1";
connectAttr "place2dTexture2.vt2" "file3.vt2";
connectAttr "place2dTexture2.vt3" "file3.vt3";
connectAttr "place2dTexture2.vc1" "file3.vc1";
connectAttr "place2dTexture2.ofs" "file3.fs";
connectAttr "file4.oc" "lambert3.c";
connectAttr "lambert3.oc" "lambert3SG.ss";
connectAttr "lambert3SG.msg" "materialInfo5.sg";
connectAttr "lambert3.msg" "materialInfo5.m";
connectAttr "file4.msg" "materialInfo5.t" -na;
connectAttr "place2dTexture3.c" "file4.c";
connectAttr "place2dTexture3.tf" "file4.tf";
connectAttr "place2dTexture3.rf" "file4.rf";
connectAttr "place2dTexture3.mu" "file4.mu";
connectAttr "place2dTexture3.mv" "file4.mv";
connectAttr "place2dTexture3.s" "file4.s";
connectAttr "place2dTexture3.wu" "file4.wu";
connectAttr "place2dTexture3.wv" "file4.wv";
connectAttr "place2dTexture3.re" "file4.re";
connectAttr "place2dTexture3.of" "file4.of";
connectAttr "place2dTexture3.r" "file4.ro";
connectAttr "place2dTexture3.n" "file4.n";
connectAttr "place2dTexture3.vt1" "file4.vt1";
connectAttr "place2dTexture3.vt2" "file4.vt2";
connectAttr "place2dTexture3.vt3" "file4.vt3";
connectAttr "place2dTexture3.vc1" "file4.vc1";
connectAttr "place2dTexture3.o" "file4.uv";
connectAttr "place2dTexture3.ofs" "file4.fs";
connectAttr "SciFi_CharacterSG.pa" ":renderPartition.st" -na;
connectAttr "Alleyway01SG.pa" ":renderPartition.st" -na;
connectAttr "lambert2SG.pa" ":renderPartition.st" -na;
connectAttr "pCube1SG.pa" ":renderPartition.st" -na;
connectAttr "lambert3SG.pa" ":renderPartition.st" -na;
connectAttr "SciFi_CharacterSG1.msg" ":defaultShaderList1.s" -na;
connectAttr "Alleyway01SG1.msg" ":defaultShaderList1.s" -na;
connectAttr "lambert2.msg" ":defaultShaderList1.s" -na;
connectAttr "blinn1.msg" ":defaultShaderList1.s" -na;
connectAttr "lambert3.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture3.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "file3.msg" ":defaultTextureList1.tx" -na;
connectAttr "file4.msg" ":defaultTextureList1.tx" -na;
dataStructure -fmt "raw" -as "name=externalContentTable:string=node:string=key:string=upath:uint32=upathcrc:string=rpath:string=roles";
applyMetadata -fmt "raw" -v "channel\nname externalContentTable\nstream\nname v1.0\nindexType numeric\nstructure externalContentTable\n0\n\"file1\" \"fileTextureName\" \"D:/Full Sail/New Library/Checked/3D/6. Buildings/Alien Buildings/alienbuildings.png\" 4009411484 \"D:/Full Sail/New Library/Checked/3D/6. Buildings/Alien Buildings/alienbuildings.png\" \"sourceImages\"\n1\n\"file3\" \"fileTextureName\" \"D:/Full Sail/Art Fixes/Our Team/level/Barrier_Concrete/Barrier.fbm/TEX_Barrier1_D.png\" 4040048355 \"D:/Full Sail/Art Fixes/Our Team/level/Barrier_Concrete/Barrier.fbm/TEX_Barrier1_D.png\" \"sourceImages\"\n2\n\"file4\" \"fileTextureName\" \"D:/Full Sail/Art Fixes/Our Team/level/Ground.jpg\" 2736081167 \"D:/Full Sail/Art Fixes/Our Team/level/Ground.jpg\" \"sourceImages\"\nendStream\nendChannel\nendAssociations\n" 
		-scn;
// End of Building_005.ma
