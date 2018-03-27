//Maya ASCII 2015 scene
//Name: Building_003.ma
//Last modified: Mon, Mar 26, 2018 01:06:52 PM
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
createNode transform -n "Building_003";
	setAttr ".rp" -type "double3" 3046.7357177734375 1506.7591552734402 -1359.8634033203125 ;
	setAttr ".sp" -type "double3" 3046.7357177734375 1506.7591552734402 -1359.8634033203125 ;
createNode mesh -n "Building_003Shape" -p "Building_003";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 258 ".uvst[0].uvsp";
	setAttr ".uvst[0].uvsp[0:249]" -type "float2" 0.41119999 0.82959998 0.4946
		 0.74610001 0.4946 0.99650002 0.41119999 0.99650002 0.25009999 0.50040001 0.0011 0.49959999
		 0.00019999999 0.75150001 0.2492 0.75239998 0.0052999998 0.73970002 0.2427 0.73970002
		 0.24420001 1.0045000315 0.0068000001 1.0045000315 0.0052999998 0.73970002 0.2427
		 0.73970002 0.24420001 1.0045000315 0.0068000001 1.0045000315 0.0014 0.49959999 0.00060000003
		 0.75150001 0.2492 0.75209999 0.25009999 0.50040001 0.24420001 0.82959998 0.24420001
		 0.74610001 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999 0.75150001 0.00019999999
		 0.75150001 0.2492 0.75239998 0.25009999 0.50040001 0.0052999998 0.73970002 0.2427
		 0.73970002 0.24420001 1.0045000315 0.24420001 1.0045000315 0.0068000001 1.0045000315
		 0.0052999998 0.73970002 0.0052999998 0.73970002 0.2427 0.73970002 0.24420001 1.0045000315
		 0.24420001 1.0045000315 0.0068000001 1.0045000315 0.0052999998 0.73970002 0.25009999
		 0.50040001 0.0011 0.49959999 0.00019999999 0.75150001 0.00019999999 0.75150001 0.2492
		 0.75239998 0.25009999 0.50040001 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999
		 0.75150001 0.00019999999 0.75150001 0.2492 0.75239998 0.25009999 0.50040001 0.0052999998
		 0.73970002 0.2427 0.73970002 0.24420001 1.0045000315 0.24420001 1.0045000315 0.0068000001
		 1.0045000315 0.0052999998 0.73970002 0.0052999998 0.73970002 0.2427 0.73970002 0.24420001
		 1.0045000315 0.24420001 1.0045000315 0.0068000001 1.0045000315 0.0052999998 0.73970002
		 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999 0.75150001 0.00019999999 0.75150001
		 0.2492 0.75239998 0.25009999 0.50040001 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999
		 0.75150001 0.00019999999 0.75150001 0.2492 0.75239998 0.25009999 0.50040001 0.0052999998
		 0.73970002 0.2427 0.73970002 0.24420001 1.0045000315 0.24420001 1.0045000315 0.0068000001
		 1.0045000315 0.0052999998 0.73970002 0.0052999998 0.73970002 0.2427 0.73970002 0.24420001
		 1.0045000315 0.24420001 1.0045000315 0.0068000001 1.0045000315 0.0052999998 0.73970002
		 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999 0.75150001 0.00019999999 0.75150001
		 0.2492 0.75239998 0.25009999 0.50040001 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999
		 0.75150001 0.00019999999 0.75150001 0.2492 0.75239998 0.25009999 0.50040001 0.0052999998
		 0.73970002 0.2427 0.73970002 0.24420001 1.0045000315 0.24420001 1.0045000315 0.0068000001
		 1.0045000315 0.0052999998 0.73970002 0.0052999998 0.73970002 0.2427 0.73970002 0.24420001
		 1.0045000315 0.24420001 1.0045000315 0.0068000001 1.0045000315 0.0052999998 0.73970002
		 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999 0.75150001 0.00019999999 0.75150001
		 0.2492 0.75239998 0.25009999 0.50040001 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999
		 0.75150001 0.00019999999 0.75150001 0.2492 0.75239998 0.25009999 0.50040001 0.0052999998
		 0.73970002 0.2427 0.73970002 0.24420001 1.0045000315 0.24420001 1.0045000315 0.0068000001
		 1.0045000315 0.0052999998 0.73970002 0.0052999998 0.73970002 0.2427 0.73970002 0.24420001
		 1.0045000315 0.24420001 1.0045000315 0.0068000001 1.0045000315 0.0052999998 0.73970002
		 0.25009999 0.50040001 0.0011 0.49959999 0.00019999999 0.75150001 0.00019999999 0.75150001
		 0.2492 0.75239998 0.25009999 0.50040001 0.49970001 0.63889998 0.75279999 0.63889998
		 0.75279999 0.74830002 0.57950002 0.74900001 0.4982 0.63349998 0.7489 0.63410002 0.67159998
		 0.74989998 0.4982 0.74870002 0.7489 0.74989998 0.75029999 0.63559997 0.75029999 0.75059998
		 0.67180002 0.75059998 0.67180002 0.63559997 0.75029999 0.63559997 0.75029999 0.75059998
		 0.49939999 0.75059998 0.49939999 0.63559997 0.75029999 0.63559997 0.75029999 0.63559997
		 0.75029999 0.75059998 0.67180002 0.75059998 0.67180002 0.75059998 0.67180002 0.63559997
		 0.75029999 0.63559997 0.75029999 0.63559997 0.75029999 0.75059998 0.49939999 0.75059998
		 0.49939999 0.75059998 0.49939999 0.63559997 0.75029999 0.63559997 0.74519998 0.63800001
		 0.74519998 0.7543 0.66729999 0.63800001 0.49630001 0.7543 0.49630001 0.63709998 0.74769998
		 0.75019997 0.49880001 0.75019997 0.57779998 0.63370001 0.74879998 0.63419998 0.49990001
		 0.63370001 0.68089998 0.75379997 0.68089998 0.63669997 0.7507 0.63669997 0.7507 0.75379997
		 0.50220001 0.75400001 0.50220001 0.63679999 0.56950003 0.63679999 0.56950003 0.75400001
		 0.68089998 0.75379997 0.68089998 0.63669997 0.7507 0.63669997 0.7507 0.63669997 0.7507
		 0.75379997 0.68089998 0.75379997 0.50220001 0.75400001 0.50220001 0.63679999 0.56950003
		 0.63679999 0.56950003 0.63679999 0.56950003 0.75400001 0.50220001 0.75400001 0.49970001
		 0.74900001 0.41119999 0.94419998 0.41119999 0.82959998 0.2969 0.94440001 0.41119999
		 0.82959998 0.2965 0.82959998 0.75029999 0.63559997 0.75029999 0.75059998 0.49939999
		 0.75059998 0.49939999 0.75059998 0.49939999 0.63559997 0.75029999 0.63559997 0.75029999
		 0.63559997 0.75029999 0.75059998 0.67180002 0.75059998 0.67180002 0.75059998 0.67180002
		 0.63559997 0.75029999 0.63559997 0.75029999 0.63559997 0.75029999 0.75059998 0.49939999
		 0.75059998 0.49939999 0.75059998 0.49939999 0.63559997 0.75029999 0.63559997 0.75029999
		 0.63559997 0.75029999 0.75059998 0.67180002 0.75059998 0.67180002 0.75059998 0.67180002
		 0.63559997 0.75029999 0.63559997 0.2965 0.82959998 0.41119999 0.82959998 0.2969 0.94440001
		 0.41119999 0.82959998 0.41119999 0.94419998 0.2969 0.94440001 0.50040001 0.75379997
		 0.50040001 0.63669997 0.68080002 0.63669997 0.68080002 0.75379997 0.56959999 0.75400001
		 0.56959999 0.63679999 0.75260001 0.63679999 0.75260001 0.75400001 0.50040001 0.75379997
		 0.50040001 0.63669997 0.68080002 0.63669997 0.68080002 0.63669997;
	setAttr ".uvst[0].uvsp[250:257]" 0.68080002 0.75379997 0.50040001 0.75379997
		 0.56959999 0.75400001 0.56959999 0.63679999 0.75260001 0.63679999 0.75260001 0.63679999
		 0.75260001 0.75400001 0.56959999 0.75400001;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr -s 54 ".vt[0:53]"  2795.8034668 3013.51831055 -1108.93493652
		 2293.9465332 3013.51831055 -607.078430176 3799.52514648 3013.51831055 -607.078369141
		 3799.52514648 3013.51831055 -1108.93493652 2293.9465332 5.4569682e-012 -607.078430176
		 3799.52514648 5.4569682e-012 -607.078369141 3799.52514648 501.8571167 -607.078369141
		 2293.9465332 501.8571167 -607.078430176 3799.52514648 5.4569682e-012 -1108.93493652
		 3799.52514648 501.8571167 -1108.93493652 2795.80322266 5.4569682e-012 -2112.6484375
		 2293.94628906 5.4569682e-012 -2112.6484375 2293.94628906 501.8571167 -2112.6484375
		 2795.80322266 501.8571167 -2112.6484375 2795.80322266 3013.51831055 -2112.6484375
		 2293.94628906 3013.51831055 -2112.6484375 3799.52514648 1003.71343994 -607.078369141
		 2293.9465332 1003.71343994 -607.078430176 3799.52514648 1003.71343994 -1108.93493652
		 2293.94628906 1003.71343994 -2112.6484375 2795.80322266 1003.71343994 -2112.6484375
		 3799.52514648 1505.57067871 -607.078369141 2293.9465332 1505.57067871 -607.078430176
		 3799.52514648 1505.57067871 -1108.93493652 2293.94628906 1505.57067871 -2112.6484375
		 2795.80322266 1505.57067871 -2112.6484375 3799.52514648 2007.42773438 -607.078369141
		 2293.9465332 2007.42773438 -607.078430176 3799.52514648 2007.42773438 -1108.93493652
		 2293.94628906 2007.42773438 -2112.6484375 2795.80322266 2007.42773438 -2112.6484375
		 3799.52514648 2511.66137695 -607.078369141 2293.9465332 2509.28393555 -607.078430176
		 3799.52514648 2509.28393555 -1108.93493652 2293.94628906 2511.66137695 -2112.6484375
		 2795.80322266 2509.28393555 -2112.6484375 2795.8034668 5.4569682e-012 -1108.93493652
		 2795.8034668 499.93960571 -1108.93493652 3485.37133789 501.8571167 -1108.93493652
		 2795.8034668 501.8571167 -1798.49609375 2795.8034668 1003.71343994 -1798.49609375
		 2795.8034668 1505.57067871 -1798.49609375 2795.8034668 2007.42773438 -1798.49609375
		 2795.8034668 2509.28393555 -1798.49609375 2795.8034668 2513.57861328 -1108.93493652
		 3485.37133789 2509.28393555 -1108.93493652 3485.37133789 2007.42773438 -1108.93493652
		 3485.37133789 1505.57067871 -1108.93493652 3485.37133789 1003.71343994 -1108.93493652
		 3486.36645508 501.8571167 -1796.088745117 3486.36645508 1003.71343994 -1796.088745117
		 3486.36645508 1505.57067871 -1796.088745117 3486.36645508 2007.42773438 -1796.088745117
		 3486.36645508 2509.28393555 -1796.088745117;
	setAttr -s 153 ".ed[0:152]"  0 1 0 1 2 0 2 3 0 3 0 0 4 5 0 5 6 0 6 7 0
		 7 4 0 5 8 0 8 9 0 9 5 0 9 6 0 10 11 0 11 12 0 12 13 0 13 10 0 7 12 0 12 4 0 11 4 0
		 0 14 0 14 15 0 15 1 0 6 16 0 16 7 0 16 17 0 17 7 0 9 18 0 18 6 0 18 16 0 12 19 0
		 19 13 0 19 20 0 20 13 0 17 12 0 17 19 0 16 21 0 21 17 0 21 22 0 22 17 0 18 23 0 23 16 0
		 23 21 0 19 24 0 24 20 0 24 25 0 25 20 0 22 19 0 22 24 0 21 26 0 26 22 0 26 27 0 27 22 0
		 23 28 0 28 21 0 28 26 0 24 29 0 29 25 0 29 30 0 30 25 0 27 24 0 27 29 0 26 31 0 31 27 0
		 31 32 0 32 27 0 28 33 0 33 26 0 33 31 0 29 34 0 34 30 0 34 35 0 35 30 0 32 29 0 32 34 0
		 31 2 0 2 32 0 1 32 0 33 3 0 3 31 0 34 15 0 15 35 0 14 35 0 1 34 0 8 36 0 36 37 0
		 37 8 0 37 38 0 38 8 0 36 10 0 10 39 0 39 36 0 39 37 0 13 39 0 20 40 0 40 13 0 40 39 0
		 25 41 0 41 20 0 41 40 0 30 42 0 42 25 0 42 41 0 35 43 0 43 30 0 43 42 0 14 43 0 0 44 0
		 44 14 0 44 43 0 3 45 0 45 0 0 45 44 0 33 45 0 28 46 0 46 33 0 46 45 0 23 47 0 47 28 0
		 47 46 0 18 48 0 48 23 0 48 47 0 9 38 0 38 18 0 38 48 0 37 49 0 49 38 0 39 49 0 40 50 0
		 50 39 0 50 49 0 41 51 0 51 40 0 51 50 0 42 52 0 52 41 0 52 51 0 43 53 0 53 42 0 53 52 0
		 44 53 0 45 53 0 46 52 0 52 45 0 47 51 0 51 46 0 48 50 0 50 47 0 49 48 0 2 0 1 5 7 1
		 11 13 1 0 15 1;
	setAttr -s 292 ".n";
	setAttr ".n[0:165]" -type "float3"  0 0.0050612036 0 0 0.0050612036 0 0 0.0050612036
		 0 0 0.0050612036 0 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 1.123813e-018
		 0 0.0050612036 1.123813e-018 0 0.0050612036 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -0.0050612036
		 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036
		 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 0 0.0050612036
		 0 0 0.0050612036 0 0 0.0050612036 0 0 0.0050612036 0 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036
		 1.123813e-018 0 0.0050612036 1.123813e-018 0 0.0050612036 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018
		 -0.0050612036 0 1.123813e-018 -0.0050612036 0 1.123813e-018 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036
		 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018
		 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018;
	setAttr ".n[166:291]" -type "float3"  0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 0.0050612036
		 0 -1.123813e-018 0.0050612036 0 -1.123813e-018 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 -1.123813e-018
		 0 -0.0050612036 -1.123813e-018 0 -0.0050612036 1.417137e-005 -0.0050611836 -3.1466762e-021
		 1.417137e-005 -0.0050611836 -3.1466762e-021 1.417137e-005 -0.0050611836 -3.1466762e-021
		 -3.1466762e-021 -0.0050611836 -1.417137e-005 -3.1466762e-021 -0.0050611836 -1.417137e-005
		 -3.1466762e-021 -0.0050611836 -1.417137e-005 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 1.7714214e-005
		 0 -0.0050611733 1.7714214e-005 0 -0.0050611733 -6.9676404e-021 0.0050611072 -3.1379463e-005
		 -6.9676404e-021 0.0050611072 -3.1379463e-005 -6.9676404e-021 0.0050611072 -3.1379463e-005
		 3.1379463e-005 0.0050611072 -6.9676404e-021 3.1379463e-005 0.0050611072 -6.9676404e-021
		 3.1379463e-005 0.0050611072 -6.9676404e-021 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985 0 7.085685e-006 0.0050611985
		 0 7.085685e-006 0.0050611985 0 7.085685e-006;
	setAttr -s 100 -ch 300 ".fc[0:99]" -type "polyFaces" 
		f 3 1 149 0
		mu 0 3 1 2 0
		f 3 -150 2 3
		mu 0 3 0 2 3
		f 3 4 150 7
		mu 0 3 4 5 7
		f 3 -151 5 6
		mu 0 3 7 5 6
		f 3 8 9 10
		mu 0 3 8 9 10
		f 3 11 -6 -11
		mu 0 3 10 11 8
		f 3 12 151 15
		mu 0 3 12 13 15
		f 3 -152 13 14
		mu 0 3 15 13 14
		f 3 -8 16 17
		mu 0 3 16 17 18
		f 3 -14 18 -18
		mu 0 3 18 19 16
		f 3 -1 152 21
		mu 0 3 1 0 21
		f 3 -153 19 20
		mu 0 3 21 0 20
		f 3 -7 22 23
		mu 0 3 22 23 24
		f 3 24 25 -24
		mu 0 3 25 26 27
		f 3 -12 26 27
		mu 0 3 28 29 30
		f 3 28 -23 -28
		mu 0 3 31 32 33
		f 3 -15 29 30
		mu 0 3 34 35 36
		f 3 31 32 -31
		mu 0 3 37 38 39
		f 3 -17 -26 33
		mu 0 3 40 41 42
		f 3 34 -30 -34
		mu 0 3 43 44 45
		f 3 -25 35 36
		mu 0 3 46 47 48
		f 3 37 38 -37
		mu 0 3 49 50 51
		f 3 -29 39 40
		mu 0 3 52 53 54
		f 3 41 -36 -41
		mu 0 3 55 56 57
		f 3 -32 42 43
		mu 0 3 58 59 60
		f 3 44 45 -44
		mu 0 3 61 62 63
		f 3 -35 -39 46
		mu 0 3 64 65 66
		f 3 47 -43 -47
		mu 0 3 67 68 69
		f 3 -38 48 49
		mu 0 3 70 71 72
		f 3 50 51 -50
		mu 0 3 73 74 75
		f 3 -42 52 53
		mu 0 3 76 77 78
		f 3 54 -49 -54
		mu 0 3 79 80 81
		f 3 -45 55 56
		mu 0 3 82 83 84
		f 3 57 58 -57
		mu 0 3 85 86 87
		f 3 -48 -52 59
		mu 0 3 88 89 90
		f 3 60 -56 -60
		mu 0 3 91 92 93
		f 3 -51 61 62
		mu 0 3 94 95 96
		f 3 63 64 -63
		mu 0 3 97 98 99
		f 3 -55 65 66
		mu 0 3 100 101 102
		f 3 67 -62 -67
		mu 0 3 103 104 105
		f 3 -58 68 69
		mu 0 3 106 107 108
		f 3 70 71 -70
		mu 0 3 109 110 111
		f 3 -61 -65 72
		mu 0 3 112 113 114
		f 3 73 -69 -73
		mu 0 3 115 116 117
		f 3 -64 74 75
		mu 0 3 118 119 120
		f 3 -2 76 -76
		mu 0 3 121 122 123
		f 3 -68 77 78
		mu 0 3 124 125 126
		f 3 -3 -75 -79
		mu 0 3 127 128 129
		f 3 -71 79 80
		mu 0 3 130 131 132
		f 3 -21 81 -81
		mu 0 3 133 134 135
		f 3 -74 -77 82
		mu 0 3 136 137 138
		f 3 -22 -80 -83
		mu 0 3 139 140 141
		f 3 83 84 85
		mu 0 3 142 143 144
		f 3 86 87 -86
		mu 0 3 144 145 142
		f 3 88 89 90
		mu 0 3 146 147 148
		f 3 91 -85 -91
		mu 0 3 148 149 146
		f 3 -16 92 -90
		mu 0 3 147 150 148
		f 3 -33 93 94
		mu 0 3 151 152 153
		f 3 95 -93 -95
		mu 0 3 153 154 151
		f 3 -46 96 97
		mu 0 3 155 156 157
		f 3 98 -94 -98
		mu 0 3 157 158 159
		f 3 -59 99 100
		mu 0 3 160 161 162
		f 3 101 -97 -101
		mu 0 3 163 164 165
		f 3 -72 102 103
		mu 0 3 166 167 168
		f 3 104 -100 -104
		mu 0 3 169 170 171
		f 3 -82 105 -103
		mu 0 3 172 173 174
		f 3 -20 106 107
		mu 0 3 173 175 176
		f 3 108 -106 -108
		mu 0 3 176 174 173
		f 3 -4 109 110
		mu 0 3 177 178 179
		f 3 111 -107 -111
		mu 0 3 179 180 177
		f 3 -78 112 -110
		mu 0 3 178 181 179
		f 3 -66 113 114
		mu 0 3 182 183 184
		f 3 115 -113 -115
		mu 0 3 184 185 182
		f 3 -53 116 117
		mu 0 3 186 187 188
		f 3 118 -114 -118
		mu 0 3 188 189 186
		f 3 -40 119 120
		mu 0 3 190 191 192
		f 3 121 -117 -121
		mu 0 3 193 194 195
		f 3 -27 122 123
		mu 0 3 196 197 198
		f 3 124 -120 -124
		mu 0 3 199 200 201
		f 3 -10 -88 -123
		mu 0 3 202 142 145
		f 3 -87 125 126
		mu 0 3 203 204 205
		f 3 -92 127 -126
		mu 0 3 206 207 205
		f 3 -96 128 129
		mu 0 3 208 209 210
		f 3 130 -128 -130
		mu 0 3 211 212 213
		f 3 -99 131 132
		mu 0 3 214 215 216
		f 3 133 -129 -133
		mu 0 3 217 218 219
		f 3 -102 134 135
		mu 0 3 220 221 222
		f 3 136 -132 -136
		mu 0 3 223 224 225
		f 3 -105 137 138
		mu 0 3 226 227 228
		f 3 139 -135 -139
		mu 0 3 229 230 231
		f 3 -109 140 -138
		mu 0 3 232 233 234
		f 3 -112 141 -141
		mu 0 3 235 236 237
		f 3 -116 142 143
		mu 0 3 238 239 240
		f 3 -140 -142 -144
		mu 0 3 240 241 238
		f 3 -119 144 145
		mu 0 3 242 243 244
		f 3 -137 -143 -146
		mu 0 3 244 245 242
		f 3 -122 146 147
		mu 0 3 246 247 248
		f 3 -134 -145 -148
		mu 0 3 249 250 251
		f 3 -125 -127 148
		mu 0 3 252 253 254
		f 3 -131 -147 -149
		mu 0 3 255 256 257;
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
connectAttr "Building_003Shape.iog" "lambert2SG.dsm" -na;
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
// End of Building_003.ma
