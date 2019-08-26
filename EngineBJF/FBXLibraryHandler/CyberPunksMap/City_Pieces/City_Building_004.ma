//Maya ASCII 2015 scene
//Name: City_Building_004.ma
//Last modified: Tue, Mar 20, 2018 03:08:29 PM
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
	setAttr ".v" no;
	setAttr ".t" -type "double3" -16886.248599564038 7502.8887751737793 -1645.2114956829141 ;
	setAttr ".r" -type "double3" -18.938352731918442 623.79999999995164 2.5444437451708134e-014 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".fcp" 1000000;
	setAttr ".coi" 19240.559864376177;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" -1396.4512329101562 57.805624008178711 2111.8790893554687 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 454.63621875869956 23077.291951732368 2311.0674453567267 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".fcp" 1000000;
	setAttr ".coi" 16473.261013283962;
	setAttr ".ow" 20180.796599344478;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 624.83366722363371 165.48332316223554 5437.9160128694366 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 5435.9476562500004;
	setAttr ".ow" 1586.7485742956449;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 5578.9988705020405 115.28067534251929 -140.68030302150328 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 5435.9476562500004;
	setAttr ".ow" 1583.5900573039542;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "Building_004";
	setAttr ".rp" -type "double3" -778.11768427644802 5.456968210637567e-012 -766.23479853848767 ;
	setAttr ".sp" -type "double3" -778.11768427644802 5.456968210637567e-012 -766.23479853848767 ;
createNode mesh -n "Building_004Shape" -p "Building_004";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 175 ".uvst[0].uvsp[0:174]" -type "float2" 0.21960001 0.55309999
		 0.25209999 0.70429999 -0.0019 0.70539999 0.0307 0.55269998 0.2106 0.51090002 0.2106
		 0.70499998 0.038800001 0.70499998 0.038800001 0.51090002 0.1596 0.85189998 0.1657
		 0.74489999 0.25189999 0.7446 0.20290001 0.85170001 0.2149 0.68519998 0.2395 0.5424
		 0.0062000002 0.5424 0.023399999 0.68519998 0.2106 0.51090002 0.2106 0.70499998 0.038800001
		 0.70499998 0.038800001 0.70499998 0.038800001 0.51090002 0.2106 0.51090002 0.1033
		 0.85210001 0.092900001 0.74510002 0.21960001 0.55309999 0.25209999 0.70429999 -0.0019
		 0.70539999 -0.0019 0.70539999 0.0307 0.55269998 0.21960001 0.55309999 0.2106 0.51090002
		 0.2106 0.70499998 0.038800001 0.70499998 0.038800001 0.70499998 0.038800001 0.51090002
		 0.2106 0.51090002 0.051100001 0.85229999 0.0063999998 0.74550003 0.22930001 0.55449998
		 0.25740001 0.70319998 0.0019 0.70289999 0.035599999 0.55409998 0.2106 0.51090002
		 0.2106 0.70499998 0.038800001 0.70499998 0.038800001 0.70499998 0.038800001 0.51090002
		 0.2106 0.51090002 0.0307 0.55269998 -0.0019 0.70539999 0.25209999 0.70429999 0.25209999
		 0.70429999 0.21960001 0.55309999 0.0307 0.55269998 0.2106 0.51090002 0.2106 0.70499998
		 0.038800001 0.70499998 0.038800001 0.70499998 0.038800001 0.51090002 0.2106 0.51090002
		 0.1033 0.85210001 0.093000002 0.74510002 0.0065000001 0.74550003 0.051100001 0.85229999
		 0.1033 0.85210001 0.2133 0.68580002 0.2379 0.54299998 0.0046000001 0.54299998 0.0217
		 0.68580002 0.2106 0.51090002 0.2106 0.70499998 0.038800001 0.70499998 0.038800001
		 0.70499998 0.038800001 0.51090002 0.2106 0.51090002 0.15979999 0.85189998 0.16590001
		 0.74489999 0.1033 0.85210001 0.21960001 0.55309999 0.25209999 0.70429999 -0.0019
		 0.70539999 -0.0019 0.70539999 0.0307 0.55269998 0.21960001 0.55309999 0.2106 0.51090002
		 0.2106 0.70499998 0.038800001 0.70499998 0.038800001 0.70499998 0.038800001 0.51090002
		 0.2106 0.51090002 0.2032 0.85170001 0.25209999 0.7446 0.22930001 0.55449998 0.25740001
		 0.70319998 0.0019 0.70289999 0.0019 0.70289999 0.035599999 0.55409998 0.22930001
		 0.55449998 0.2422 0.75059998 0.2886 0.86320001 0.4472 0.86210001 0.49880001 0.75160003
		 0.34869999 0.35249999 0.37709999 0.35210001 0.37639999 0.39340001 0.34920001 0.39379999
		 0.2886 0.86320001 0.2422 0.75059998 0.49880001 0.75160003 0.49880001 0.75160003 0.4472
		 0.86210001 0.2886 0.86320001 0.43380001 0.2739 0.29280001 0.27579999 0.24770001 0.25760001
		 0.479 0.2545 0.43110001 0.46970001 0.47580001 0.48789999 0.29370001 0.4716 0.2489
		 0.491 0.43360001 0.3127 0.29249999 0.31459999 0.3087 0.85039997 0.4395 0.8502 0.4813
		 0.74989998 0.26530001 0.75089997 0.294 0.433 0.4314 0.43110001 0.4395 0.8502 0.3087
		 0.85039997 0.26530001 0.75089997 0.26530001 0.75089997 0.4813 0.74989998 0.4395 0.8502
		 0.40599999 0.32449999 0.31999999 0.3256 0.4043 0.41999999 0.32120001 0.42120001 0.40599999
		 0.32440001 0.31999999 0.3256 0.30450001 0.68949997 0.3046 0.53079998 0.4253 0.52920002
		 0.42519999 0.68800002 0.32120001 0.42109999 0.4043 0.41999999 0.30790001 0.53039998
		 0.30770001 0.68910003 0.42829999 0.68760002 0.4285 0.52880001 0.2106 0.51090002 0.2106
		 0.70499998 0.038800001 0.70499998 0.038800001 0.70499998 0.038800001 0.51090002 0.2106
		 0.51090002 0.4043 0.41999999 0.3353 0.41499999 0.39019999 0.41429999 0.4043 0.41999999
		 0.31999999 0.3256 0.33419999 0.33129999 0.31999999 0.3256 0.39179999 0.33050001 0.4043
		 0.41999999 0.32390001 0.75139999 0.41589999 0.75120002 0.39629999 0.88139999 0.35080001
		 0.8811 0.41589999 0.75120002 0.32390001 0.75139999 0.35080001 0.8811 0.35080001 0.8811
		 0.39629999 0.88139999 0.41589999 0.75120002;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr -s 56 ".pt[0:55]" -type "float3"  -285.46497 586.95557 -547.07709 
		-178.50885 5.4569682e-012 -499.04144 -178.21513 5.4569682e-012 -1077.1606 -282.92972 
		586.95557 -1027.5269 -416.22235 586.95557 -605.80408 -420.8418 581.38293 -956.93256 
		-497.30634 5.4569682e-012 -642.22058 -512.01129 5.5708447 -829.30054 -483.19873 586.95557 
		-316.61707 -419.36475 5.4569682e-012 -218.32358 -561.24017 586.95557 -436.78638 -609.63318 
		5.4569682e-012 -511.30273 -953.19128 586.95557 -244.29871 -990.78436 5.4569682e-012 
		-129.32251 -907.23206 586.95557 -384.86304 -812.15649 5.4569682e-012 -474.5553 -1275.5088 
		586.95557 -520.61761 -1383.3932 5.4569682e-012 -465.90009 -1143.6168 586.95557 -587.513 
		-1266.3718 586.95557 -987.62427 -1373.3262 5.4569682e-012 -1035.6606 -1135.613 586.95557 
		-928.89801 -1054.5289 5.4569682e-012 -892.48151 -1069.8167 5.4569682e-012 -695.24799 
		-1068.6362 586.95557 -1218.0835 -1132.4702 5.4569682e-012 -1316.3771 -990.59558 586.95557 
		-1097.9158 -942.20178 5.4569682e-012 -1023.3979 -608.41589 586.95557 -1298.7621 -570.82208 
		5.4569682e-012 -1413.7383 -652.73932 581.38293 -1155.7358 -764.78015 5.5708447 -1045.8042 
		-838.53357 1567.5326 -733.70734 -809.47882 1567.5326 -708.81976 -723.50995 1564.231 
		-810.34424 -751.25006 1564.231 -834.10608 -913.97229 586.5069 -470.30234 -1058.1644 
		586.5069 -593.91705 -505.93286 581.8316 -950.2193 -646.36078 581.8316 -1070.6066 
		-832.89832 1107.4224 -565.06622 -977.13885 1107.4224 -688.62335 -586.62195 1102.7471 
		-855.90472 -727.09717 1102.7471 -976.23584 -837.06549 1106.9713 -617.08331 -925.05347 
		1106.9713 -692.45374 -638.34467 1103.2004 -851.76208 -723.29401 1103.2004 -924.52942 
		-837.18036 890.35382 -616.94781 -925.16907 890.35382 -692.31891 -638.4599 886.58057 
		-851.62726 -723.40967 886.58057 -924.39539 -721.43787 886.81622 -897.59491 -665.26801 
		886.81622 -849.47998 -898.17151 890.11823 -694.30438 -839.34052 890.11823 -643.9101;
	setAttr -s 56 ".vt[0:55]"  2.22576499 1.29500496 -1.78247499 2.711128 0 -2.16834593
		 -0.0042699999 0 -3.57335711 -0.025319999 1.29500496 -2.96088004 1.63238895 1.29500496 -1.31073594
		 -0.028495001 1.28270996 -2.14154792 1.264431 0 -1.018206 0.34979001 0.012291 -1.40333605
		 2.82842588 1.29500496 -0.29394501 3.44521308 0 -0.35519999 2.074371099 1.29500496 -0.219055
		 1.60678506 0 -0.17261501 2.027084112 1.29500496 2.089747906 2.47599006 0 2.54552102
		 1.47827494 1.29500496 1.53254497 1.28771996 0 0.86809498 -0.053675 1.29500496 2.93317389
		 -0.058534998 0 3.57288408 -0.047734998 1.29500496 2.15110397 -2.22557092 1.29500496 1.75638998
		 -2.71093011 0 2.14225411 -1.63219094 1.29500496 1.28464496 -1.26423502 0 0.99211502
		 -0.374715 0 1.54280496 -2.82822394 1.29500496 0.26785499 -3.44500709 0 0.32911 -2.074177027 1.29500496 0.192965
		 -1.60658503 0 0.146525 -2.08988595 1.29500496 -2.090224981 -2.53879189 0 -2.54600096
		 -1.52553904 1.28270996 -1.534729 -1.28108597 0.012291 -0.74143499 0.0061349999 3.45846009 0.36282
		 0.19360501 3.45846009 0.28674001 -0.074649997 3.45117593 -0.36364999 -0.25364 3.45117593 -0.291015
		 1.060498953 1.29401505 1.35677004 0.12965 1.29401505 1.73408496 -0.20355 1.28369999 -1.72547495
		 -1.11010003 1.28369999 -1.35800898 0.81212503 2.44331503 0.74579 -0.118575 2.44331503 1.123474
		 0.043650001 2.43300009 -1.11739504 -0.86274898 2.43300009 -0.74957001 0.55761999 2.44232011 0.63907498
		 -0.01011 2.44232011 0.86946499 -0.062465001 2.43400002 -0.86433399 -0.61058998 2.43400002 -0.6419
		 0.55797499 1.96439505 0.63994497 -0.0097599998 1.96439505 0.87033498 -0.062109999 1.95606995 -0.863464
		 -0.61023998 1.95606995 -0.64103001 -0.47953999 1.95659006 -0.58522499 -0.11711 1.95659006 -0.73229998
		 0.046459999 1.96387506 0.738675 0.42605999 1.96387506 0.58463001;
	setAttr -s 141 ".ed[0:140]"  0 1 0 1 2 0 2 3 0 3 0 0 4 0 0 3 4 0 3 5 0
		 5 4 0 6 4 0 5 6 0 5 7 0 7 6 0 8 9 0 9 1 0 1 8 0 0 8 0 10 8 0 0 10 0 4 10 0 11 10 0
		 4 11 0 6 11 0 12 13 0 13 9 0 9 12 0 8 12 0 14 12 0 8 14 0 10 14 0 15 14 0 10 15 0
		 11 15 0 16 17 0 17 13 0 13 16 0 12 16 0 18 16 0 12 18 0 14 18 0 19 20 0 20 17 0 17 19 0
		 16 19 0 21 19 0 16 21 0 18 21 0 22 21 0 18 22 0 18 23 0 23 22 0 24 25 0 25 20 0 20 24 0
		 19 24 0 26 24 0 19 26 0 21 26 0 27 26 0 21 27 0 22 27 0 28 29 0 29 25 0 25 28 0 24 28 0
		 30 28 0 24 30 0 26 30 0 27 31 0 31 26 0 31 30 0 2 29 0 29 3 0 28 3 0 15 7 0 7 14 0
		 5 14 0 32 33 0 33 34 0 34 35 0 35 32 0 18 30 0 30 23 0 31 23 0 36 37 0 37 18 0 18 36 0
		 14 36 0 38 36 0 14 38 0 5 38 0 39 38 0 5 39 0 5 30 0 30 39 0 37 39 0 30 37 0 40 41 0
		 41 37 0 36 40 0 42 40 0 36 42 0 38 42 0 43 42 0 39 43 0 41 43 0 39 41 0 44 45 0 45 41 0
		 40 44 0 46 44 0 42 46 0 47 46 0 42 47 0 43 47 0 45 47 0 48 49 0 49 45 0 44 48 0 50 48 0
		 44 50 0 46 50 0 51 50 0 47 51 0 49 51 0 47 49 0 28 5 0 51 52 0 52 50 0 52 53 0 53 50 0
		 49 54 0 54 52 0 48 55 0 55 54 0 53 55 0 52 35 0 34 53 0 54 32 0 32 52 0 55 33 0 34 55 0;
	setAttr -s 266 ".n";
	setAttr ".n[0:165]" -type "float3"  0.0043184455 0.001264509 -1.435035e-005
		 0.0043121623 0.0012682297 -1.8250959e-005 0.004337322 0.0012532223 -2.8943848e-006
		 0.0043460908 0.0012479213 2.6062887e-006 -1.0678955e-005 0.0022014466 -3.3470908e-006
		 0 0.0022014512 0 0 0.0022014512 0 -6.596512e-005 0.002201264 -2.0284426e-005 -6.596512e-005
		 0.002201264 -2.0284426e-005 -1.0678955e-005 0.0022014466 -3.3470908e-006 -0.0042705545
		 0.0011447568 -0.0014382027 -0.0046580136 0.0010331125 7.2855262e-005 -0.0046580136
		 0.0010331125 7.2855262e-005 -0.004342054 0.0012400291 0.00038453098 -0.004342054
		 0.0012400291 0.00038453098 -0.0042705545 0.0011447568 -0.0014382027 0.0032298556
		 0.0013105172 0.0027453331 0.0032298556 0.0013105172 0.0027453331 0.0032298556 0.0013105172
		 0.0027453331 0.0032298556 0.0013105172 0.0027453331 0.0032298556 0.0013105172 0.0027453331
		 0.0032298556 0.0013105172 0.0027453331 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512
		 0 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0 -0.0022561545 0.0011104075 -0.0039573591
		 -0.0035048847 0.0010780221 -0.0029788783 -0.0035048847 0.0010780221 -0.0029788783
		 -0.0035048847 0.0010780221 -0.0029788783 -0.0042705545 0.0011447568 -0.0014382027
		 -0.0022561545 0.0011104075 -0.0039573591 0.00068062893 0.0012734778 0.0042491425
		 0.00068156893 0.0012748825 0.0042465678 0.00068156893 0.0012748825 0.0042465678 0.00067591091
		 0.0012671509 0.0042607407 0.00067591091 0.0012671509 0.0042607407 0.00068062893 0.0012734778
		 0.0042491425 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0
		 0 0.0022014512 0 0 0.0022014512 0 -0.0007609746 0.00099285448 -0.0046466864 -0.00072478584
		 0.00097089721 -0.0046790033 -0.00072478584 0.00097089721 -0.0046790033 -0.00085031649
		 0.0010459006 -0.0045636245 -0.0022561545 0.0011104075 -0.0039573591 -0.0007609746
		 0.00099285448 -0.0046466864 -0.0027499159 0.0013052403 0.003238216 -0.0027499159
		 0.0013052403 0.003238216 -0.0027499159 0.0013052403 0.003238216 -0.0027499159 0.0013052403
		 0.003238216 -0.0027499159 0.0013052403 0.003238216 -0.0027499159 0.0013052403 0.003238216
		 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512
		 0 0 0.0022014512 0 -0.0043035354 0.001273119 -5.718118e-005 -0.0043010064 0.0012746161
		 -5.6044482e-005 -0.0043010064 0.0012746161 -5.6044482e-005 -0.004314255 0.0012667283
		 -6.4067128e-005 -0.004314255 0.0012667283 -6.4067128e-005 -0.0043035354 0.001273119
		 -5.718118e-005 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512
		 0 0 0.0022014512 0 0 0.0022014512 0 0.0042929887 0.0010840276 0.001628981 0.0046418556
		 0.001045511 8.6960958e-005 0.0046418556 0.001045511 8.6960958e-005 0.0048339716 0.00086938171
		 0.00035203662 0.0048339716 0.00086938171 0.00035203662 0.0042929887 0.0010840276
		 0.001628981 -0.0032298556 0.0013105172 -0.0027453331 -0.0032298556 0.0013105172 -0.0027453331
		 -0.0032298556 0.0013105172 -0.0027453331 -0.0032298556 0.0013105172 -0.0027453331
		 -0.0032298556 0.0013105172 -0.0027453331 -0.0032298556 0.0013105172 -0.0027453331
		 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512 0 0 0.0022014512
		 0 0 0.0022014512 0 0.0021265184 0.0011084196 0.0040316428 0.0035048847 0.0010780221
		 0.0029788783 0.0035048847 0.0010780221 0.0029788783 0.0035048847 0.0010780221 0.0029788783
		 0.0042929887 0.0010840276 0.001628981 0.0021265184 0.0011084196 0.0040316428 -0.00075774308
		 0.0012687205 -0.0042442582 -0.0007568032 0.0012673181 -0.0042468333 -0.0007568032
		 0.0012673181 -0.0042468333 -0.00076244521 0.0012750189 -0.0042325617 -0.00076244521
		 0.0012750189 -0.0042325617 -0.00075774308 0.0012687205 -0.0042442582 1.1667315e-005
		 0.0022013653 4.5095905e-005 1.021162e-005 0.0022013236 5.597674e-005 1.021162e-005
		 0.0022013236 5.597674e-005 2.0284622e-005 0.002201427 -1.3579865e-005 2.0284622e-005
		 0.002201427 -1.3579865e-005 1.1667315e-005 0.0022013653 4.5095905e-005 0.00058727141
		 0.0010247667 0.004632079 0.0021265184 0.0011084196 0.0040316428 0.0007323905 0.0010987906
		 0.0045124129 0.0007323905 0.0010987906 0.0045124129 0.00079579419 0.0011307094 0.0044560414
		 0.00079579419 0.0011307094 0.0044560414 0.0028013557 0.0012590737 -0.0032985366 0.0028013557
		 0.0012590737 -0.0032985366 0.0028013557 0.0012590737 -0.0032985366 0.0026988252 0.0013100725
		 -0.0032698358 0.0026988252 0.0013100725 -0.0032698358 0.0026988252 0.0013100725 -0.0032698358
		 0.0040236055 0.00021089462 0.0033744609 0.0040236055 0.00021089462 0.0033744609 0.0040236055
		 0.00021089462 0.0033744609 0.0040200544 0.00019417678 0.0033844428 0.0040200544 0.00019417678
		 0.0033844428 0.0040200544 0.00019417678 0.0033844428 2.2186598e-005 0.0022014051
		 -2.5884565e-005 2.2186598e-005 0.0022014051 -2.5884565e-005 2.2186598e-005 0.0022014051
		 -2.5884565e-005 2.2186598e-005 0.0022014051 -2.5884565e-005 -0.0039893445 0.0002108902
		 -0.0034148959 -0.0039893445 0.0002108902 -0.0034148959 -0.0039893445 0.0002108902
		 -0.0034148959 -0.0039831595 0.00018271824 -0.003431398 -0.0039831595 0.00018271824
		 -0.003431398 -0.0039831595 0.00018271824 -0.003431398 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 6.7048577e-006 0.0022014466
		 -7.6718625e-006 6.7048577e-006 0.0022014466 -7.6718625e-006 -0.0025057676 0.0014952895
		 0.0029517217 -0.0025057676 0.0014952895 0.0029517217;
	setAttr ".n[166:265]" -type "float3"  -0.0025057676 0.0014952895 0.0029517217
		 -0.0025057676 0.0014952895 0.0029517217 0.0040420503 -1.034682e-005 0.0033901369
		 0.0040420503 -1.034682e-005 0.0033901369 0.0040420503 -1.034682e-005 0.0033901369
		 0.0040350789 6.1640631e-006 0.0033984836 0.0040350789 6.1640631e-006 0.0033984836
		 0.0040350789 6.1640631e-006 0.0033984836 0.0025102985 0.001491939 -0.0029576079 0.0025102985
		 0.001491939 -0.0029576079 0.0025102985 0.001491939 -0.0029576079 0.0025102985 0.001491939
		 -0.0029576079 -0.0039973822 1.6070593e-005 -0.0034425601 -0.0039973822 1.6070593e-005
		 -0.0034425601 -0.0039973822 1.6070593e-005 -0.0034425601 -0.0040081111 -9.6863851e-006
		 -0.0034302073 -0.0040081111 -9.6863851e-006 -0.0034302073 -0.0040081111 -9.6863851e-006
		 -0.0034302073 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 0.0034132947 -7.0446436e-006 -0.0040225522 0.0034132947 -7.0446436e-006
		 -0.0040225522 0.0034132947 -7.0446436e-006 -0.0040225522 0.0034132947 -7.0446436e-006
		 -0.0040225522 -0.0040419665 0 -0.0033903292 -0.0040419665 0 -0.0033903292 -0.0040419665
		 0 -0.0033903292 -0.0040419665 0 -0.0033903292 -0.0040419665 0 -0.0033903292 -0.0040419665
		 0 -0.0033903292 -0.0034132947 7.0446436e-006 0.0040225522 -0.0034132947 7.0446436e-006
		 0.0040225522 -0.0034132947 7.0446436e-006 0.0040225522 -0.0034132947 7.0446436e-006
		 0.0040225522 0.0039974903 0 0.0034426523 0.0039974903 0 0.0034426523 0.0039974903
		 0 0.0034426523 0.0039974903 0 0.0034426523 0.0039974903 0 0.0034426523 0.0039974903
		 0 0.0034426523 -3.4416851e-005 0.0022013367 4.1207029e-005 -3.3949313e-005 0.0022013388
		 4.0962637e-005 -3.3949313e-005 0.0022013388 4.0962637e-005 -3.5819456e-005 0.0022013301
		 4.194022e-005 -3.5819456e-005 0.0022013301 4.194022e-005 -3.4416851e-005 0.0022013367
		 4.1207029e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 1.0625764e-005 0.0022014403 -1.2697887e-005 1.0625764e-005 0.0022014403
		 -1.2697887e-005 0.0031843511 0.00079270516 -0.0037527385 0.0031843511 0.00079270516
		 -0.0037527385 0.0031843511 0.00079270516 -0.0037527385 0.0031843511 0.00079270516
		 -0.0037527385 -0.0039725872 0.0002390732 -0.0034237565 -0.0039725872 0.0002390732
		 -0.0034237565 -0.0039725872 0.0002390732 -0.0034237565 -0.0039713238 0.00023994716
		 -0.0034248696 -0.0039713238 0.00023994716 -0.0034248696 -0.0039713238 0.00023994716
		 -0.0034248696 -0.0031772966 0.00080396119 0.0037449612 -0.0031772966 0.00080396119
		 0.0037449612 -0.0031772966 0.00080396119 0.0037449612 -0.0031772966 0.00080396119
		 0.0037449612 0.0040190662 0.00023952889 0.0033688867 0.0040190662 0.00023952889 0.0033688867
		 0.0040190662 0.00023952889 0.0033688867 0.0040206271 0.00023864613 0.0033673861 0.0040206271
		 0.00023864613 0.0033673861 0.0040206271 0.00023864613 0.0033673861;
	setAttr -s 84 -ch 266 ".fc[0:83]" -type "polyFaces" 
		f 4 0 1 2 3
		mu 0 4 0 1 2 3
		f 3 4 -4 5
		mu 0 3 4 5 6
		f 3 6 7 -6
		mu 0 3 6 7 4
		f 3 8 -8 9
		mu 0 3 8 9 10
		f 3 10 11 -10
		mu 0 3 10 11 8
		f 3 12 13 14
		mu 0 3 12 13 14
		f 3 -1 15 -15
		mu 0 3 14 15 12
		f 3 16 -16 17
		mu 0 3 16 17 18
		f 3 -5 18 -18
		mu 0 3 19 20 21
		f 3 19 -19 20
		mu 0 3 22 23 9
		f 3 -9 21 -21
		mu 0 3 9 8 22
		f 3 22 23 24
		mu 0 3 24 25 26
		f 3 -13 25 -25
		mu 0 3 27 28 29
		f 3 26 -26 27
		mu 0 3 30 31 32
		f 3 -17 28 -28
		mu 0 3 33 34 35
		f 3 29 -29 30
		mu 0 3 36 37 23
		f 3 -20 31 -31
		mu 0 3 23 22 36
		f 3 32 33 34
		mu 0 3 38 39 40
		f 3 -23 35 -35
		mu 0 3 40 41 38
		f 3 36 -36 37
		mu 0 3 42 43 44
		f 3 -27 38 -38
		mu 0 3 45 46 47
		f 3 39 40 41
		mu 0 3 48 49 50
		f 3 -33 42 -42
		mu 0 3 51 52 53
		f 3 43 -43 44
		mu 0 3 54 55 56
		f 3 -37 45 -45
		mu 0 3 57 58 59
		f 3 46 -46 47
		mu 0 3 60 61 62
		f 3 48 49 -48
		mu 0 3 62 63 64
		f 3 50 51 52
		mu 0 3 65 66 67
		f 3 -40 53 -53
		mu 0 3 67 68 65
		f 3 54 -54 55
		mu 0 3 69 70 71
		f 3 -44 56 -56
		mu 0 3 72 73 74
		f 3 57 -57 58
		mu 0 3 75 76 61
		f 3 -47 59 -59
		mu 0 3 61 77 75
		f 3 60 61 62
		mu 0 3 78 79 80
		f 3 -51 63 -63
		mu 0 3 81 82 83
		f 3 64 -64 65
		mu 0 3 84 85 86
		f 3 -55 66 -66
		mu 0 3 87 88 89
		f 3 -58 67 68
		mu 0 3 76 75 90
		f 3 69 -67 -69
		mu 0 3 90 91 76
		f 3 -3 70 71
		mu 0 3 92 93 94
		f 3 -61 72 -72
		mu 0 3 95 96 97
		f 3 -30 73 74
		mu 0 3 98 99 100
		f 3 -11 75 -75
		mu 0 3 100 101 98
		f 4 76 77 78 79
		mu 0 4 102 103 104 105
		f 3 -49 80 81
		mu 0 3 106 107 108
		f 3 -70 82 -82
		mu 0 3 109 110 111
		f 3 83 84 85
		mu 0 3 112 113 114
		f 3 -39 86 -86
		mu 0 3 114 115 112
		f 3 87 -87 88
		mu 0 3 116 112 115
		f 3 -76 89 -89
		mu 0 3 115 117 116
		f 3 90 -90 91
		mu 0 3 118 116 117
		f 3 92 93 -92
		mu 0 3 117 119 118
		f 3 94 -94 95
		mu 0 3 113 118 119
		f 3 -81 -85 -96
		mu 0 3 119 114 113
		f 4 96 97 -84 98
		mu 0 4 120 121 113 112
		f 3 99 -99 100
		mu 0 3 122 123 124
		f 3 -88 101 -101
		mu 0 3 124 125 122
		f 4 102 -102 -91 103
		mu 0 4 126 127 116 118
		f 3 104 -104 105
		mu 0 3 128 129 130
		f 3 -95 -98 -106
		mu 0 3 131 132 133
		f 4 106 107 -97 108
		mu 0 4 134 135 121 120
		f 4 109 -109 -100 110
		mu 0 4 136 134 120 127
		f 3 111 -111 112
		mu 0 3 137 136 127
		f 3 -103 113 -113
		mu 0 3 127 126 137
		f 4 114 -114 -105 -108
		mu 0 4 135 137 126 121
		f 4 115 116 -107 117
		mu 0 4 138 139 135 134
		f 3 118 -118 119
		mu 0 3 140 141 142
		f 3 -110 120 -120
		mu 0 3 142 143 140
		f 4 121 -121 -112 122
		mu 0 4 144 145 136 137
		f 3 123 -123 124
		mu 0 3 146 147 148
		f 3 -115 -117 -125
		mu 0 3 148 149 146
		f 3 -7 -73 125
		mu 0 3 150 151 152
		f 3 -65 -93 -126
		mu 0 3 153 154 155
		f 3 -122 126 127
		mu 0 3 156 144 157
		f 3 128 129 -128
		mu 0 3 157 158 159
		f 4 -124 130 131 -127
		mu 0 4 144 160 161 157
		f 4 -116 132 133 -131
		mu 0 4 162 138 163 161
		f 4 -119 -130 134 -133
		mu 0 4 138 164 158 163
		f 4 -129 135 -79 136
		mu 0 4 158 157 105 104
		f 3 -132 137 138
		mu 0 3 165 166 167
		f 3 -80 -136 -139
		mu 0 3 167 168 165
		f 4 -134 139 -77 -138
		mu 0 4 161 163 103 102
		f 3 -135 -137 140
		mu 0 3 169 170 171
		f 3 -78 -140 -141
		mu 0 3 172 173 174;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
	setAttr ".hfd" -type "dataPolyComponent" Index_Data Face 0 ;
createNode shadingEngine -n "SciFi_CharacterSG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
createNode shadingEngine -n "Alleyway01SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
createNode lightLinker -s -n "lightLinker1";
	setAttr -s 6 ".lnk";
	setAttr -s 6 ".slnk";
createNode displayLayerManager -n "layerManager";
	setAttr ".cdl" 4;
	setAttr -s 9 ".dli[1:8]"  1 2 3 4 5 6 7 8;
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
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n"
		+ "                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n"
		+ "                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 0\n"
		+ "                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n"
		+ "            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n"
		+ "            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 0\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n"
		+ "            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n"
		+ "                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n"
		+ "                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n"
		+ "                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n"
		+ "            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n"
		+ "            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n"
		+ "                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n"
		+ "                -maxConstantTransparency 1\n                -rendererName \"vp2Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n"
		+ "                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n"
		+ "            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n"
		+ "            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n"
		+ "                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"smoothShaded\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 0\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 1\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n"
		+ "                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n"
		+ "                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                $editorName;\n            modelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n"
		+ "            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 1\n            -shadows 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n"
		+ "            outlinerEditor -e \n                -docTag \"isolOutln_fromSeln\" \n                -showShapes 0\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 1\n                -showAssets 1\n                -showContainedOnly 1\n                -showPublishedAsConnected 0\n                -showContainerContents 1\n                -ignoreDagHierarchy 0\n                -expandConnections 0\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n"
		+ "                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 0\n                -ignoreHiddenAttribute 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -docTag \"isolOutln_fromSeln\" \n            -showShapes 0\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n"
		+ "            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\toutlinerPanel -e -to $panelName;\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n"
		+ "\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n"
		+ "                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n"
		+ "\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1.25\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n"
		+ "                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n"
		+ "                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1.25\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -stackedCurves 0\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -displayNormalized 0\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -classicMode 1\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n"
		+ "\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n"
		+ "                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n"
		+ "\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n"
		+ "                -showMuteInfo 0\n                -organizeByLayer 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n"
		+ "                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n"
		+ "                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"sequenceEditorPanel\" -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n"
		+ "                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n"
		+ "                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n"
		+ "                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n"
		+ "                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -defaultPinnedState 0\n                -ignoreAssets 1\n                -additiveGraphingMode 0\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -keyReleaseCommand \"nodeEdKeyReleaseCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                $editorName;;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"createNodePanel\" -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"Stereo\" (localizedPanelLabel(\"Stereo\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"Stereo\" -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels `;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n"
		+ "                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n"
		+ "                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n"
		+ "                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                -useCustomBackground 1\n                $editorName;\n            stereoCameraView -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Stereo\")) -mbv $menusOkayInPanels  $panelName;\nstring $editorName = ($panelName+\"Editor\");\n            stereoCameraView -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -ignorePanZoom 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n"
		+ "                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -objectFilterShowInHUD 1\n                -isFiltered 0\n                -colorResolution 4 4 \n                -bumpResolution 4 4 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n"
		+ "                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 0\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -imagePlane 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -particleInstancers 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n"
		+ "                -nParticles 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -pluginShapes 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -motionTrails 1\n                -clipGhosts 1\n                -greasePencils 1\n                -shadows 0\n                -displayMode \"centerEye\" \n                -viewColor 0 0 0 1 \n                -useCustomBackground 1\n                $editorName;\n            stereoCameraView -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n"
		+ "\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
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
	setAttr ".ftn" -type "string" "D:\\Full Sail\\Art Fixes\\Our Team\\level\\Barrier_Concrete\\Barrier.fbm\\TEX_Barrier1_D.png";
createNode place2dTexture -n "place2dTexture2";
select -ne :time1;
	setAttr ".o" 0;
select -ne :renderPartition;
	setAttr -s 6 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderUtilityList1;
	setAttr -s 2 ".u";
select -ne :defaultRenderingList1;
select -ne :defaultTextureList1;
	setAttr -s 2 ".tx";
connectAttr "SciFi_CharacterSG.msg" "materialInfo1.sg";
connectAttr "Alleyway01SG.msg" "materialInfo2.sg";
relationship "link" ":lightLinker1" "SciFi_CharacterSG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "Alleyway01SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "lambert2SG.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" "pCube1SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "SciFi_CharacterSG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "Alleyway01SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "lambert2SG.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" "pCube1SG.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "file1.oc" "lambert2.c";
connectAttr "lambert2.oc" "lambert2SG.ss";
connectAttr "Building_004Shape.iog" "lambert2SG.dsm" -na;
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
connectAttr "SciFi_CharacterSG.pa" ":renderPartition.st" -na;
connectAttr "Alleyway01SG.pa" ":renderPartition.st" -na;
connectAttr "lambert2SG.pa" ":renderPartition.st" -na;
connectAttr "pCube1SG.pa" ":renderPartition.st" -na;
connectAttr "lambert2.msg" ":defaultShaderList1.s" -na;
connectAttr "blinn1.msg" ":defaultShaderList1.s" -na;
connectAttr "place2dTexture1.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "place2dTexture2.msg" ":defaultRenderUtilityList1.u" -na;
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "file1.msg" ":defaultTextureList1.tx" -na;
connectAttr "file3.msg" ":defaultTextureList1.tx" -na;
dataStructure -fmt "raw" -as "name=externalContentTable:string=node:string=key:string=upath:uint32=upathcrc:string=rpath:string=roles";
applyMetadata -fmt "raw" -v "channel\nname externalContentTable\nstream\nname v1.0\nindexType numeric\nstructure externalContentTable\n0\n\"file1\" \"fileTextureName\" \"D:/Full Sail/New Library/Checked/3D/6. Buildings/Alien Buildings/alienbuildings.png\" 4009411484 \"D:/Full Sail/New Library/Checked/3D/6. Buildings/Alien Buildings/alienbuildings.png\" \"sourceImages\"\n1\n\"file3\" \"fileTextureName\" \"D:\\\\Full Sail\\\\Art Fixes\\\\Our Team\\\\level\\\\Barrier_Concrete\\\\Barrier.fbm\\\\TEX_Barrier1_D.png\" 1287322738 \"D:/Full Sail/Art Fixes/Our Team/level/Barrier_Concrete/Barrier.fbm/TEX_Barrier1_D.png\" \"sourceImages\"\nendStream\nendChannel\nendAssociations\n" 
		-scn;
// End of City_Building_004.ma
