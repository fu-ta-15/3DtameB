xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 84;
 -0.01720;-8.12269;0.00065;,
 0.80987;-8.07827;-0.43896;,
 0.87801;-8.07827;0.00065;,
 -0.01720;-8.12269;0.00065;,
 0.61581;-8.07827;-0.81164;,
 -0.01720;-8.12269;0.00065;,
 0.32538;-8.07827;-1.06066;,
 -0.01720;-8.12269;0.00065;,
 -0.01720;-8.07827;-1.14810;,
 1.62787;-7.94553;-0.87375;,
 1.76341;-7.94553;0.00065;,
 1.24188;-7.94553;-1.61503;,
 0.66421;-7.94553;-2.11034;,
 -0.01720;-7.94553;-2.28427;,
 2.42785;-7.72590;-1.29896;,
 2.62930;-7.72590;0.00065;,
 1.63484;-7.13540;-1.98592;,
 0.99557;-7.72590;-3.13689;,
 -0.01720;-7.72590;-3.39540;,
 3.20104;-7.42179;-1.70993;,
 3.46620;-7.42179;0.00065;,
 2.44593;-7.42179;-3.16010;,
 1.31584;-7.42179;-4.12907;,
 -0.01720;-7.42179;-4.46932;,
 3.85759;-6.98859;-2.11615;,
 4.26493;-7.03655;0.00065;,
 2.77811;-6.83581;-3.88485;,
 1.38889;-6.83581;-5.07600;,
 -0.01720;-7.03655;-5.49428;,
 4.55218;-6.52641;-2.48535;,
 5.01674;-6.57438;0.00065;,
 3.30973;-6.37364;-4.56703;,
 1.67660;-6.37364;-5.96731;,
 -0.01720;-6.57438;-6.45902;,
 5.27719;-6.04035;-2.81347;,
 5.71340;-6.04035;0.00065;,
 4.03495;-6.04035;-5.19916;,
 2.17581;-6.04035;-6.79323;,
 -0.01720;-6.04035;-7.35300;,
 5.86281;-5.44031;-3.12475;,
 6.34728;-5.44031;0.00065;,
 4.48317;-5.44031;-5.77433;,
 2.41838;-5.44031;-7.54472;,
 -0.01720;-5.44031;-8.16640;,
 6.38401;-4.78084;-3.40178;,
 6.91142;-4.78084;0.00065;,
 4.88208;-4.78084;-6.28622;,
 2.63427;-4.78084;-8.21354;,
 -0.01720;-4.78084;-9.35556;,
 5.95172;-4.06916;-3.64154;,
 7.39966;-4.06916;0.00065;,
 5.22731;-4.06916;-6.72923;,
 2.82111;-4.06916;-8.79237;,
 -0.01720;-4.06916;-9.51685;,
 7.21108;-3.31307;-3.84139;,
 7.80663;-3.31307;0.00065;,
 5.51508;-3.31307;-7.09851;,
 2.97685;-3.31307;-9.37775;,
 -0.01720;-3.31307;-10.14198;,
 7.50788;-2.52086;-3.99915;,
 8.12788;-2.52086;0.00065;,
 5.74225;-2.52086;-7.39001;,
 3.46414;-2.52086;-10.33337;,
 -0.01720;-2.52086;-10.55422;,
 8.33543;-1.70119;-4.29825;,
 8.35990;-1.70119;0.00065;,
 5.90630;-1.70119;-7.60053;,
 3.55293;-1.70119;-10.50553;,
 -0.01720;-1.70119;-10.74905;,
 7.85179;-0.86306;-4.18194;,
 8.50013;-0.86306;0.00065;,
 6.00546;-0.86306;-7.72779;,
 3.24224;-0.86306;-10.09703;,
 -0.01720;-0.86306;-10.92900;,
 7.89513;-0.01564;-4.20498;,
 8.54705;-0.01564;0.00065;,
 6.03864;-0.01564;-7.77035;,
 3.26019;-0.01564;-10.15266;,
 -0.01720;-0.01564;-10.98920;,
 -0.00534;-0.01564;-6.22763;,
 -0.00723;-0.01564;-2.18791;,
 -0.00390;-0.01564;-9.31950;,
 -0.00311;-0.01564;-10.98561;,
 -0.00826;-0.01564;0.00065;;
 
 80;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 4;2,1,9,10;,
 4;1,4,11,9;,
 4;4,6,12,11;,
 4;6,8,13,12;,
 4;10,9,14,15;,
 4;9,11,16,14;,
 4;11,12,17,16;,
 4;12,13,18,17;,
 4;15,14,19,20;,
 4;14,16,21,19;,
 4;16,17,22,21;,
 4;17,18,23,22;,
 4;20,19,24,25;,
 4;19,21,26,24;,
 4;21,22,27,26;,
 4;22,23,28,27;,
 4;25,24,29,30;,
 4;24,26,31,29;,
 4;26,27,32,31;,
 4;27,28,33,32;,
 4;30,29,34,35;,
 4;29,31,36,34;,
 4;31,32,37,36;,
 4;32,33,38,37;,
 4;35,34,39,40;,
 4;34,36,41,39;,
 4;36,37,42,41;,
 4;37,38,43,42;,
 4;40,39,44,45;,
 4;39,41,46,44;,
 4;41,42,47,46;,
 4;42,43,48,47;,
 4;45,44,49,50;,
 4;44,46,51,49;,
 4;46,47,52,51;,
 4;47,48,53,52;,
 4;50,49,54,55;,
 4;49,51,56,54;,
 4;51,52,57,56;,
 4;52,53,58,57;,
 4;55,54,59,60;,
 4;54,56,61,59;,
 4;56,57,62,61;,
 4;57,58,63,62;,
 4;60,59,64,65;,
 4;59,61,66,64;,
 4;61,62,67,66;,
 4;62,63,68,67;,
 4;65,64,69,70;,
 4;64,66,71,69;,
 4;66,67,72,71;,
 4;67,68,73,72;,
 4;70,69,74,75;,
 4;69,71,76,74;,
 4;71,72,77,76;,
 4;72,73,78,77;,
 4;79,80,74,76;,
 4;81,79,76,77;,
 3;81,77,82;,
 4;80,83,75,74;,
 4;2,75,83,0;,
 4;2,10,70,75;,
 4;10,15,65,70;,
 4;15,20,60,65;,
 4;20,25,55,60;,
 4;25,30,50,55;,
 4;30,35,45,50;,
 3;35,40,45;,
 3;0,83,82;,
 4;8,0,82,73;,
 4;13,8,73,68;,
 4;68,63,18,13;,
 4;63,58,23,18;,
 4;58,53,28,23;,
 4;53,48,33,28;,
 4;48,43,38,33;;
 
 MeshMaterialList {
  1;
  80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  83;
  0.032385;-0.999157;-0.025242;,
  0.019750;-0.996806;-0.077376;,
  0.099016;-0.994968;-0.015348;,
  0.091524;-0.995364;-0.029551;,
  0.070113;-0.996041;-0.054653;,
  0.037980;-0.996719;-0.071473;,
  0.039553;-0.987128;-0.154961;,
  0.197204;-0.979886;-0.030568;,
  0.206202;-0.965256;-0.160506;,
  0.295404;-0.920135;-0.257075;,
  0.207680;-0.959692;-0.189365;,
  0.059458;-0.970671;-0.232941;,
  0.293742;-0.954800;-0.045533;,
  0.194250;-0.954134;-0.227805;,
  0.267033;-0.923069;-0.276833;,
  0.250575;-0.949822;-0.187218;,
  0.126655;-0.926949;-0.353163;,
  0.404267;-0.911785;-0.072218;,
  0.302113;-0.933823;-0.191581;,
  0.251727;-0.932376;-0.259440;,
  0.220319;-0.933481;-0.282971;,
  0.208329;-0.884811;-0.416784;,
  0.490138;-0.865497;-0.103344;,
  0.465848;-0.860544;-0.206033;,
  0.395277;-0.845304;-0.359468;,
  0.281035;-0.865307;-0.415045;,
  0.199531;-0.890072;-0.409827;,
  0.540960;-0.833783;-0.110308;,
  0.463069;-0.865172;-0.192472;,
  0.320996;-0.901829;-0.289251;,
  0.231100;-0.904527;-0.358363;,
  0.158117;-0.848980;-0.504214;,
  0.627075;-0.771735;-0.105842;,
  0.559831;-0.806041;-0.192063;,
  0.404165;-0.854652;-0.325916;,
  0.239656;-0.864840;-0.441154;,
  0.169042;-0.796803;-0.580111;,
  0.720126;-0.684805;-0.111626;,
  0.679211;-0.699857;-0.221074;,
  0.539069;-0.727822;-0.423886;,
  0.307399;-0.775054;-0.552084;,
  0.240689;-0.638513;-0.731006;,
  0.899844;-0.386750;-0.201754;,
  0.873163;-0.395252;-0.285240;,
  0.679463;-0.550429;-0.485136;,
  0.370214;-0.657180;-0.656549;,
  0.238175;-0.538675;-0.808147;,
  0.880900;-0.412790;-0.231561;,
  0.863990;-0.417807;-0.280998;,
  0.701191;-0.520255;-0.487510;,
  0.390976;-0.571976;-0.721098;,
  0.163394;-0.628141;-0.760751;,
  0.826286;-0.540315;-0.159094;,
  0.793472;-0.551255;-0.257914;,
  0.662624;-0.577541;-0.476840;,
  0.370265;-0.621604;-0.690299;,
  0.101615;-0.437918;-0.893254;,
  0.890375;-0.441558;-0.110723;,
  0.845918;-0.455568;-0.277274;,
  0.730248;-0.452500;-0.511841;,
  0.413108;-0.467220;-0.781695;,
  0.114562;-0.044473;-0.992420;,
  0.980712;-0.175397;-0.086251;,
  0.933015;-0.187195;-0.307311;,
  0.797262;-0.115370;-0.592506;,
  0.460630;-0.046681;-0.886364;,
  0.205188;0.032855;-0.978171;,
  0.990908;0.062935;-0.118918;,
  0.948220;0.059193;-0.312049;,
  0.783882;0.054833;-0.618483;,
  0.459853;0.045732;-0.886817;,
  0.246734;-0.068676;-0.966647;,
  0.986723;-0.054628;-0.152952;,
  0.948658;-0.056980;-0.311129;,
  0.781700;-0.061776;-0.620587;,
  0.460175;-0.067854;-0.885232;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.999981;0.005381;0.003008;,
  -0.999999;0.001103;-0.000469;,
  -0.999983;0.004830;0.003242;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  80;
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,1,5;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;4,5,10,9;,
  4;5,1,6,10;,
  4;7,8,13,12;,
  4;8,9,14,13;,
  4;9,10,15,14;,
  4;10,6,11,15;,
  4;12,13,18,17;,
  4;13,14,19,18;,
  4;14,15,20,19;,
  4;15,11,16,20;,
  4;17,18,23,22;,
  4;18,19,24,23;,
  4;19,20,25,24;,
  4;20,16,21,25;,
  4;22,23,28,27;,
  4;23,24,29,28;,
  4;24,25,30,29;,
  4;25,21,26,30;,
  4;27,28,33,32;,
  4;28,29,34,33;,
  4;29,30,35,34;,
  4;30,26,31,35;,
  4;32,33,38,37;,
  4;33,34,39,38;,
  4;34,35,40,39;,
  4;35,31,36,40;,
  4;37,38,43,42;,
  4;38,39,44,43;,
  4;39,40,45,44;,
  4;40,36,41,45;,
  4;42,43,48,47;,
  4;43,44,49,48;,
  4;44,45,50,49;,
  4;45,41,46,50;,
  4;47,48,53,52;,
  4;48,49,54,53;,
  4;49,50,55,54;,
  4;50,46,51,55;,
  4;52,53,58,57;,
  4;53,54,59,58;,
  4;54,55,60,59;,
  4;55,51,56,60;,
  4;57,58,63,62;,
  4;58,59,64,63;,
  4;59,60,65,64;,
  4;60,56,61,65;,
  4;62,63,68,67;,
  4;63,64,69,68;,
  4;64,65,70,69;,
  4;65,61,66,70;,
  4;67,68,73,72;,
  4;68,69,74,73;,
  4;69,70,75,74;,
  4;70,66,71,75;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  3;76,76,76;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  3;77,77,77;,
  3;78,79,78;,
  4;80,78,78,80;,
  4;81,80,80,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;82,82,82,82;;
 }
 MeshTextureCoords {
  84;
  0.781250;0.000000;,
  0.812500;0.033330;,
  0.750000;0.033330;,
  0.843750;0.000000;,
  0.875000;0.033330;,
  0.906250;0.000000;,
  0.937500;0.033330;,
  0.968750;0.000000;,
  1.000000;0.033330;,
  0.812500;0.066670;,
  0.750000;0.066670;,
  0.875000;0.066670;,
  0.937500;0.066670;,
  1.000000;0.066670;,
  0.812500;0.100000;,
  0.750000;0.100000;,
  0.875000;0.100000;,
  0.937500;0.100000;,
  1.000000;0.100000;,
  0.812500;0.133330;,
  0.750000;0.133330;,
  0.875000;0.133330;,
  0.937500;0.133330;,
  1.000000;0.133330;,
  0.812500;0.166670;,
  0.750000;0.166670;,
  0.875000;0.166670;,
  0.937500;0.166670;,
  1.000000;0.166670;,
  0.812500;0.200000;,
  0.750000;0.200000;,
  0.875000;0.200000;,
  0.937500;0.200000;,
  1.000000;0.200000;,
  0.812500;0.233330;,
  0.750000;0.233330;,
  0.875000;0.233330;,
  0.937500;0.233330;,
  1.000000;0.233330;,
  0.812500;0.266670;,
  0.750000;0.266670;,
  0.875000;0.266670;,
  0.937500;0.266670;,
  1.000000;0.266670;,
  0.812500;0.300000;,
  0.750000;0.300000;,
  0.875000;0.300000;,
  0.937500;0.300000;,
  1.000000;0.300000;,
  0.812500;0.333330;,
  0.750000;0.333330;,
  0.875000;0.333330;,
  0.937500;0.333330;,
  1.000000;0.333330;,
  0.812500;0.366670;,
  0.750000;0.366670;,
  0.875000;0.366670;,
  0.937500;0.366670;,
  1.000000;0.366670;,
  0.812500;0.400000;,
  0.750000;0.400000;,
  0.875000;0.400000;,
  0.937500;0.400000;,
  1.000000;0.400000;,
  0.812500;0.433330;,
  0.750000;0.433330;,
  0.875000;0.433330;,
  0.937500;0.433330;,
  1.000000;0.433330;,
  0.812500;0.466670;,
  0.750000;0.466670;,
  0.875000;0.466670;,
  0.937500;0.466670;,
  1.000000;0.466670;,
  0.812500;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  0.937500;0.500000;,
  1.000000;0.500000;,
  0.577520;0.500000;,
  0.542720;0.500000;,
  0.653350;0.500000;,
  0.004030;0.500000;,
  0.500260;0.500000;;
 }
}
