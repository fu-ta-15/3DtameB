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
 130;
 4.69915;318.48936;-2.91255;,
 9.21900;145.17252;-6.61072;,
 5.03202;145.13728;-9.12820;,
 4.69915;318.48936;-2.91255;,
 2.91724;142.38372;-5.25447;,
 4.69915;318.48936;-2.91255;,
 6.84397;144.97179;2.77536;,
 4.69915;318.48936;-2.91255;,
 2.02809;144.91035;2.59326;,
 4.69915;318.48936;-2.91255;,
 -0.76794;144.98119;-1.76249;,
 4.69915;318.48936;-2.91255;,
 0.58412;145.07382;-5.56473;,
 4.69915;318.48936;-2.91255;,
 5.03202;145.13728;-9.12820;,
 3.25123;0.20634;-2.08025;,
 3.64413;-0.08011;-8.35261;,
 7.99415;-0.04606;-6.06459;,
 3.25123;0.20634;-2.08025;,
 8.79707;0.15719;-0.80528;,
 3.25123;0.20634;-2.08025;,
 5.46459;0.41591;3.50909;,
 3.25123;0.20634;-2.08025;,
 0.45679;0.52997;3.63188;,
 3.25123;0.20634;-2.08025;,
 -2.44998;0.37665;-0.57447;,
 3.25123;0.20634;-2.08025;,
 -1.01946;0.09298;-5.92469;,
 3.25123;0.20634;-2.08025;,
 3.64413;-0.08011;-8.35261;,
 10.70028;59.13398;-7.84673;,
 6.11579;59.25991;-11.79241;,
 8.79523;58.42058;-4.22164;,
 8.66000;59.26057;1.09239;,
 3.57158;59.41773;1.09239;,
 0.39901;59.48737;-2.88587;,
 1.53130;59.41717;-7.84673;,
 6.11579;59.25991;-11.79241;,
 26.79206;225.62896;-3.14460;,
 28.00646;224.12930;0.19775;,
 4.96018;205.46670;0.19775;,
 3.74571;206.96634;-3.14460;,
 25.57760;227.12847;0.19775;,
 2.53131;208.46604;0.19775;,
 26.79206;225.62896;-3.14460;,
 3.74571;206.96634;-3.14460;,
 39.41257;283.25782;-6.20425;,
 39.41257;283.25782;-6.20425;,
 39.41257;283.25782;-6.20425;,
 3.74571;206.96634;-0.91637;,
 3.74571;206.96634;-0.91637;,
 3.74571;206.96634;-0.91637;,
 -3.19734;203.89446;19.63406;,
 -5.69350;201.00579;20.19932;,
 3.84194;185.91922;-2.11430;,
 6.33809;188.80794;-2.67962;,
 -6.57681;203.87178;17.77033;,
 2.95856;188.78535;-4.54335;,
 -3.19734;203.89446;19.63406;,
 6.33809;188.80794;-2.67962;,
 -47.98202;263.95191;47.11184;,
 -47.98202;263.95191;47.11184;,
 -47.98202;263.95191;47.11184;,
 4.37951;187.83749;-3.11248;,
 4.37951;187.83749;-3.11248;,
 4.37951;187.83749;-3.11248;,
 -3.39880;222.88994;22.38734;,
 -2.77947;221.86729;23.12007;,
 -12.73111;214.97012;24.17681;,
 -13.35045;215.99268;23.44402;,
 -3.50028;222.86914;23.78569;,
 -13.45191;215.97202;24.84242;,
 -3.39880;222.88994;22.38734;,
 -13.35045;215.99268;23.44402;,
 15.83445;248.03609;39.68178;,
 15.83445;248.03609;39.68178;,
 15.83445;248.03609;39.68178;,
 -13.17785;215.64493;24.15444;,
 -13.17785;215.64493;24.15444;,
 -13.17785;215.64493;24.15444;,
 10.08667;250.20743;-27.48049;,
 13.64223;248.70777;-27.41644;,
 7.01209;230.42608;-4.15169;,
 3.45647;231.92574;-4.21568;,
 12.77178;251.70708;-25.14890;,
 6.14165;233.42544;-1.88415;,
 10.08667;250.20743;-27.48049;,
 3.45647;231.92574;-4.21568;,
 34.80307;303.53926;-46.40880;,
 34.80307;303.53926;-46.40880;,
 34.80307;303.53926;-46.40880;,
 5.53672;231.92574;-3.41713;,
 5.53672;231.92574;-3.41713;,
 5.53672;231.92574;-3.41713;,
 -18.23692;202.90857;-0.57483;,
 -19.30441;201.40894;-3.96693;,
 3.71998;182.74639;-2.96167;,
 4.78746;184.24605;0.43044;,
 -16.87784;204.40816;-3.86097;,
 6.14648;185.74574;-2.85571;,
 -18.23692;202.90857;-0.57483;,
 4.78746;184.24605;0.43044;,
 -50.11870;208.79583;10.80933;,
 -50.11870;208.79583;10.80933;,
 -50.11870;208.79583;10.80933;,
 4.88468;184.24605;-1.79567;,
 4.88468;184.24605;-1.79567;,
 4.88468;184.24605;-1.79567;,
 28.86724;182.07425;-14.93517;,
 31.97653;180.57460;-13.20940;,
 7.22873;165.34632;-2.33555;,
 4.50583;166.84597;-4.62292;,
 30.14349;183.57389;-11.61591;,
 5.12528;168.34560;-1.12114;,
 28.86724;182.07425;-14.93517;,
 4.50583;166.84597;-4.62292;,
 42.58416;239.70347;-18.40478;,
 42.58416;239.70347;-18.40478;,
 42.58416;239.70347;-18.40478;,
 5.61994;166.84597;-2.69320;,
 5.61994;166.84597;-2.69320;,
 5.61994;166.84597;-2.69320;,
 -39.89451;213.78218;5.55899;,
 -31.20001;213.78218;5.55899;,
 -31.20001;205.16192;4.42416;,
 -39.89451;205.16192;4.42416;,
 27.53671;270.56509;-3.74032;,
 34.14808;276.21163;-3.74032;,
 39.74645;269.65689;-4.87515;,
 33.13509;264.01016;-4.87515;;
 
 86;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,17;,
 3;18,17,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 4;30,17,16,31;,
 4;30,31,2,1;,
 4;32,19,17,30;,
 4;32,30,1,4;,
 4;33,21,19,32;,
 4;33,32,4,6;,
 4;34,23,21,33;,
 4;34,33,6,8;,
 4;35,25,23,34;,
 4;35,34,8,10;,
 4;36,27,25,35;,
 4;36,35,10,12;,
 4;37,29,27,36;,
 4;37,36,12,14;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;42,44,45,43;,
 3;46,39,38;,
 3;47,42,39;,
 3;48,44,42;,
 3;49,41,40;,
 3;50,40,43;,
 3;51,43,45;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;56,58,59,57;,
 3;60,53,52;,
 3;61,56,53;,
 3;62,58,56;,
 3;63,55,54;,
 3;64,54,57;,
 3;65,57,59;,
 4;66,67,68,69;,
 4;67,70,71,68;,
 4;70,72,73,71;,
 3;74,67,66;,
 3;75,70,67;,
 3;76,72,70;,
 3;77,69,68;,
 3;78,68,71;,
 3;79,71,73;,
 4;80,81,82,83;,
 4;81,84,85,82;,
 4;84,86,87,85;,
 3;88,81,80;,
 3;89,84,81;,
 3;90,86,84;,
 3;91,83,82;,
 3;92,82,85;,
 3;93,85,87;,
 4;94,95,96,97;,
 4;95,98,99,96;,
 4;98,100,101,99;,
 3;102,95,94;,
 3;103,98,95;,
 3;104,100,98;,
 3;105,97,96;,
 3;106,96,99;,
 3;107,99,101;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;112,114,115,113;,
 3;116,109,108;,
 3;117,112,109;,
 3;118,114,112;,
 3;119,111,110;,
 3;120,110,113;,
 3;121,113,115;,
 4;122,123,124,125;,
 4;125,124,123,122;,
 4;126,127,128,129;,
 4;129,128,127,126;;
 
 MeshMaterialList {
  2;
  86;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.511200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\tree_07.png";
   }
  }
  Material {
   0.558400;0.429600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\ELL88_kinomikitex1322.jpg";
   }
  }
 }
 MeshNormals {
  119;
  0.737237;0.014834;-0.675472;,
  0.550806;0.029727;-0.834103;,
  0.418577;0.008272;0.908144;,
  0.942736;0.023678;-0.332698;,
  -0.480707;0.006059;0.876860;,
  -0.989882;0.008083;0.141662;,
  -0.825619;0.016206;-0.563996;,
  -0.014716;-0.998892;0.044696;,
  -0.017015;-0.998929;0.043024;,
  -0.018791;-0.998888;0.043234;,
  -0.020414;-0.998754;0.045532;,
  -0.019359;-0.998702;0.047113;,
  -0.017076;-0.998687;0.048304;,
  -0.015414;-0.998796;0.046573;,
  -0.017541;-0.998811;0.045497;,
  0.574149;-0.017139;-0.818571;,
  0.955678;0.014738;0.294045;,
  0.997942;0.021542;0.060387;,
  -0.454293;0.018379;0.890663;,
  -0.983091;0.019962;0.182024;,
  -0.828182;0.008083;-0.560400;,
  0.090073;0.008620;0.995898;,
  -0.028640;0.006669;0.999568;,
  -0.972189;0.034036;-0.231713;,
  -0.632024;0.020676;-0.774673;,
  0.561243;-0.061935;-0.825331;,
  0.967696;-0.013867;0.251738;,
  0.986415;-0.018660;0.163208;,
  0.855283;0.006830;0.518116;,
  0.941032;-0.008960;0.338200;,
  -0.442401;0.059688;0.894829;,
  0.013354;0.041350;0.999056;,
  -0.002865;0.011214;0.999933;,
  -0.979166;0.055548;0.195315;,
  -0.819781;0.012118;-0.572549;,
  -0.600642;0.000851;-0.799518;,
  -0.561028;-0.012885;-0.827697;,
  0.882785;-0.215490;-0.417438;,
  0.745328;-0.463817;-0.478916;,
  0.053602;0.043409;0.997618;,
  0.545008;-0.673026;-0.500002;,
  0.000000;0.000000;1.000000;,
  -0.777140;-0.629328;0.000015;,
  -0.758329;0.445835;-0.475572;,
  -0.545009;0.673030;-0.499996;,
  0.106948;0.086612;0.990485;,
  -0.897545;0.175074;-0.404675;,
  -0.777140;-0.629328;0.000000;,
  -0.777132;-0.629338;0.000022;,
  -0.777148;-0.629318;0.000022;,
  0.372175;-0.142120;0.917217;,
  0.537524;-0.311111;0.783759;,
  -0.883891;-0.429435;-0.185264;,
  0.663252;-0.457170;0.592530;,
  -0.912491;-0.388881;-0.127013;,
  0.418349;-0.508748;-0.752436;,
  0.321779;0.738549;-0.592456;,
  0.251366;0.848269;-0.466105;,
  -0.850115;-0.467474;-0.242431;,
  0.381585;0.604484;-0.699279;,
  0.418365;-0.508740;-0.752432;,
  0.418344;-0.508764;-0.752428;,
  0.418337;-0.508740;-0.752448;,
  0.714063;-0.066872;-0.696881;,
  0.500892;-0.282783;-0.818010;,
  0.178383;-0.452239;0.873876;,
  0.234261;-0.468511;-0.851833;,
  0.332015;-0.344514;0.878110;,
  -0.830852;-0.552269;-0.068442;,
  -0.681357;0.730933;-0.038591;,
  -0.571490;0.820085;-0.029313;,
  0.018468;-0.544034;0.838860;,
  -0.777525;0.627086;-0.047094;,
  -0.830860;-0.552252;-0.068476;,
  -0.830830;-0.552301;-0.068441;,
  -0.830865;-0.552253;-0.068409;,
  -0.104812;-0.289139;-0.951532;,
  -0.204665;-0.520640;-0.828883;,
  0.907687;-0.051444;0.416483;,
  -0.288430;-0.711215;-0.641078;,
  0.950967;0.044598;0.306058;,
  -0.278489;-0.629325;0.725530;,
  -0.691537;0.589787;0.417047;,
  -0.664349;0.667891;0.335504;,
  0.843265;-0.146289;0.517207;,
  -0.709397;0.503728;0.492965;,
  -0.278507;-0.629325;0.725523;,
  -0.278476;-0.629338;0.725524;,
  -0.278483;-0.629312;0.725543;,
  -0.021966;-0.911812;0.410021;,
  -0.308234;-0.830411;0.464123;,
  -0.157780;0.162068;-0.974084;,
  -0.566297;-0.673026;0.475756;,
  0.043622;0.000003;-0.999048;,
  0.776408;-0.629319;0.033892;,
  0.427730;0.742377;0.515677;,
  0.522677;0.673027;0.523301;,
  -0.348540;0.313202;-0.883416;,
  0.326846;0.801422;0.500894;,
  0.776407;-0.629319;0.033909;,
  0.776399;-0.629330;0.033883;,
  0.776417;-0.629308;0.033884;,
  0.421619;-0.154152;-0.893574;,
  0.289898;-0.449314;-0.845030;,
  0.536723;-0.079901;0.839966;,
  0.127207;-0.696477;-0.706214;,
  0.451682;-0.117548;0.884402;,
  -0.673024;-0.629331;0.388563;,
  -0.824239;0.565254;0.033426;,
  -0.572465;0.797233;-0.191581;,
  0.616063;-0.041405;0.786608;,
  -0.937679;0.238408;0.252823;,
  -0.673022;-0.629331;0.388565;,
  -0.673026;-0.629330;0.388563;,
  -0.673023;-0.629333;0.388561;,
  0.000000;0.130521;-0.991446;,
  0.000000;-0.130521;0.991446;,
  -0.084767;0.099250;-0.991445;,
  0.084767;-0.099250;0.991445;;
  86;
  3;0,1,1;,
  3;21,2,2;,
  3;0,3,3;,
  3;21,4,22;,
  3;23,5,4;,
  3;23,6,5;,
  3;23,24,6;,
  3;14,7,8;,
  3;14,8,9;,
  3;14,9,10;,
  3;14,10,11;,
  3;14,11,12;,
  3;14,12,13;,
  3;14,13,7;,
  4;15,25,25,15;,
  4;15,15,1,1;,
  4;16,26,27,28;,
  4;16,28,2,2;,
  4;17,29,26,16;,
  4;17,16,3,3;,
  4;18,30,31,32;,
  4;18,32,22,4;,
  4;19,33,30,18;,
  4;19,18,4,5;,
  4;20,34,33,19;,
  4;20,19,5,6;,
  4;35,36,34,20;,
  4;35,20,6,24;,
  4;38,38,40,40;,
  4;39,39,41,41;,
  4;43,43,44,44;,
  3;37,38,38;,
  3;45,39,39;,
  3;46,43,43;,
  3;42,47,48;,
  3;42,48,49;,
  3;42,49,47;,
  4;51,51,53,53;,
  4;52,52,54,54;,
  4;56,56,57,57;,
  3;50,51,51;,
  3;58,52,52;,
  3;59,56,56;,
  3;55,60,61;,
  3;55,61,62;,
  3;55,62,60;,
  4;64,64,66,66;,
  4;65,65,67,67;,
  4;69,69,70,70;,
  3;63,64,64;,
  3;71,65,65;,
  3;72,69,69;,
  3;68,73,74;,
  3;68,74,75;,
  3;68,75,73;,
  4;77,77,79,79;,
  4;78,78,80,80;,
  4;82,82,83,83;,
  3;76,77,77;,
  3;84,78,78;,
  3;85,82,82;,
  3;81,86,87;,
  3;81,87,88;,
  3;81,88,86;,
  4;90,90,92,92;,
  4;91,91,93,93;,
  4;95,95,96,96;,
  3;89,90,90;,
  3;97,91,91;,
  3;98,95,95;,
  3;94,99,100;,
  3;94,100,101;,
  3;94,101,99;,
  4;103,103,105,105;,
  4;104,104,106,106;,
  4;108,108,109,109;,
  3;102,103,103;,
  3;110,104,104;,
  3;111,108,108;,
  3;107,112,113;,
  3;107,113,114;,
  3;107,114,112;,
  4;115,115,115,115;,
  4;116,116,116,116;,
  4;117,117,117,117;,
  4;118,118,118,118;;
 }
 MeshTextureCoords {
  130;
  0.071430;0.000000;,
  0.142860;0.000000;,
  0.000000;0.000000;,
  0.214290;0.000000;,
  0.285710;0.000000;,
  0.357140;0.000000;,
  0.428570;0.000000;,
  0.500000;0.000000;,
  0.571430;0.000000;,
  0.642860;0.000000;,
  0.714290;0.000000;,
  0.785710;0.000000;,
  0.857140;0.000000;,
  0.928570;0.000000;,
  1.000000;0.000000;,
  0.071430;1.000000;,
  0.000000;1.000000;,
  0.142860;1.000000;,
  0.214290;1.000000;,
  0.285710;1.000000;,
  0.357140;1.000000;,
  0.428570;1.000000;,
  0.500000;1.000000;,
  0.571430;1.000000;,
  0.642860;1.000000;,
  0.714290;1.000000;,
  0.785710;1.000000;,
  0.857140;1.000000;,
  0.928570;1.000000;,
  1.000000;1.000000;,
  0.142860;0.587900;,
  0.000000;0.587040;,
  0.285710;0.587900;,
  0.428570;0.587040;,
  0.571430;0.585960;,
  0.714290;0.585480;,
  0.857140;0.585960;,
  1.000000;0.587040;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.500000;0.000000;,
  0.833330;0.000000;,
  0.166670;1.000000;,
  0.500000;1.000000;,
  0.833330;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.500000;0.000000;,
  0.833330;0.000000;,
  0.166670;1.000000;,
  0.500000;1.000000;,
  0.833330;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.500000;0.000000;,
  0.833330;0.000000;,
  0.166670;1.000000;,
  0.500000;1.000000;,
  0.833330;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.500000;0.000000;,
  0.833330;0.000000;,
  0.166670;1.000000;,
  0.500000;1.000000;,
  0.833330;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.500000;0.000000;,
  0.833330;0.000000;,
  0.166670;1.000000;,
  0.500000;1.000000;,
  0.833330;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.000000;,
  0.500000;0.000000;,
  0.833330;0.000000;,
  0.166670;1.000000;,
  0.500000;1.000000;,
  0.833330;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
