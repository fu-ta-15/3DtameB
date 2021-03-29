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
 167;
 -0.00266;2.86672;-0.00367;,
 0.38557;5.30178;-1.78864;,
 -0.00266;5.30178;-1.89267;,
 -0.00266;2.86672;-0.00367;,
 0.66977;5.30178;-1.50444;,
 -0.00266;2.86672;-0.00367;,
 0.77379;2.77088;-0.00367;,
 -0.00266;2.86672;-0.00367;,
 0.66977;2.77088;0.38456;,
 -0.00266;2.86672;-0.00367;,
 0.38557;2.77088;0.66876;,
 -0.00266;2.86672;-0.00367;,
 -0.00266;2.77088;0.77279;,
 -0.00266;2.86672;-0.00367;,
 -0.39089;2.77088;0.66876;,
 -0.00266;2.86672;-0.00367;,
 -0.67510;2.77088;0.38456;,
 -0.00266;2.86672;-0.00367;,
 -0.77911;2.77088;-0.00367;,
 -0.00266;2.86672;-0.00367;,
 -0.67510;5.30178;-1.50444;,
 -0.00266;2.86672;-0.00367;,
 -0.39089;5.30178;-1.78864;,
 -0.00266;2.86672;-0.00367;,
 -0.00266;5.30178;-1.89267;,
 0.74734;4.75908;-2.41524;,
 -0.00266;4.75908;-2.61621;,
 1.29637;4.75908;-1.86621;,
 1.49734;2.48991;-0.00367;,
 1.29637;2.48991;0.74633;,
 0.74734;2.48991;1.29537;,
 -0.00266;2.48991;1.49633;,
 -0.75266;2.48991;1.29537;,
 -1.30170;2.48991;0.74633;,
 -1.50266;2.48991;-0.00367;,
 -1.30170;4.75908;-1.86621;,
 -0.75266;4.75908;-2.41524;,
 -0.00266;4.75908;-2.61621;,
 1.05800;3.89571;-2.95332;,
 -0.00266;3.89571;-3.23753;,
 1.83446;3.89571;-2.17687;,
 2.11865;2.04295;-0.00367;,
 1.83446;2.04295;1.05699;,
 1.05800;2.04295;1.83345;,
 -0.00266;2.04295;2.11765;,
 -1.06333;2.04295;1.83345;,
 -1.83978;2.04295;1.05699;,
 -2.12398;2.04295;-0.00367;,
 -1.83978;3.89571;-2.17687;,
 -1.06333;3.89571;-2.95332;,
 -0.00266;3.89571;-3.23753;,
 1.29637;2.77054;-3.36621;,
 -0.00266;2.77054;-3.71429;,
 2.24734;2.77054;-2.41524;,
 2.59541;1.46047;-0.00367;,
 2.24734;1.46047;1.29537;,
 1.29637;1.46047;2.24633;,
 -0.00266;1.46047;2.59441;,
 -1.30170;1.46047;2.24633;,
 -2.25266;1.46047;1.29537;,
 -2.60074;1.46047;-0.00367;,
 -2.25266;2.77054;-2.41524;,
 -1.30171;2.77054;-3.36621;,
 -0.00266;2.77054;-3.71429;,
 1.44623;1.46028;-3.62576;,
 -0.00266;1.46028;-4.01399;,
 2.50688;1.46028;-2.56509;,
 2.89511;0.78214;-0.00367;,
 2.50688;0.78214;1.44522;,
 1.44623;0.78214;2.50588;,
 -0.00266;0.78214;2.89411;,
 -1.45155;0.78214;2.50588;,
 -2.51221;0.78214;1.44522;,
 -2.90044;0.78214;-0.00367;,
 -2.51221;1.46028;-2.56509;,
 -1.45156;1.46028;-3.62576;,
 -0.00266;1.46028;-4.01399;,
 1.49734;0.05422;-3.71429;,
 -0.00266;0.05422;-4.11621;,
 2.59541;0.05422;-2.61621;,
 2.99734;0.05422;-0.00367;,
 2.59541;0.05422;1.49633;,
 1.49734;0.05422;2.59441;,
 -0.00266;0.05422;2.99633;,
 -1.50266;0.05422;2.59441;,
 -2.60074;0.05422;1.49633;,
 -3.00266;0.05422;-0.00367;,
 -2.60074;0.05422;-2.61621;,
 -1.50266;0.05422;-3.71429;,
 -0.00266;0.05422;-4.11621;,
 1.44623;-1.35185;-3.62576;,
 -0.00266;-1.35185;-4.01399;,
 2.50688;-1.35185;-2.56509;,
 2.89511;-0.67371;-0.00367;,
 2.50688;-0.67371;1.44522;,
 1.44623;-0.67371;2.50588;,
 -0.00266;-0.67371;2.89411;,
 -1.45155;-0.67371;2.50588;,
 -2.51221;-0.67371;1.44522;,
 -2.90044;-0.67371;-0.00367;,
 -2.51221;-1.35185;-2.56509;,
 -1.45156;-1.35185;-3.62576;,
 -0.00266;-1.35185;-4.01399;,
 1.29637;-2.66211;-3.36621;,
 -0.00266;-2.66211;-3.71429;,
 2.24734;-2.66211;-2.41524;,
 2.59541;-1.35204;-0.00367;,
 2.24734;-1.35204;1.29537;,
 1.29637;-1.35204;2.24633;,
 -0.00266;-1.35204;2.59441;,
 -1.30170;-1.35204;2.24633;,
 -2.25266;-1.35204;1.29537;,
 -2.60074;-1.35204;-0.00367;,
 -2.25266;-2.66211;-2.41524;,
 -1.30171;-2.66211;-3.36621;,
 -0.00266;-2.66211;-3.71429;,
 1.05800;-3.78725;-2.95332;,
 -0.00266;-3.78725;-3.23753;,
 1.83446;-3.78725;-2.17687;,
 2.11865;-1.93453;-0.00367;,
 1.83446;-1.93453;1.05699;,
 1.05800;-1.93453;1.83345;,
 -0.00266;-1.93453;2.11765;,
 -1.06333;-1.93453;1.83345;,
 -1.83978;-1.93453;1.05699;,
 -2.12398;-1.93453;-0.00367;,
 -1.83978;-3.78725;-2.17687;,
 -1.06333;-3.78725;-2.95332;,
 -0.00266;-3.78725;-3.23753;,
 0.74734;-4.65065;-2.41524;,
 -0.00266;-4.65065;-2.61621;,
 1.29637;-4.65065;-1.86621;,
 1.49734;-2.38150;-0.00367;,
 1.29637;-2.38150;0.74633;,
 0.74734;-2.38150;1.29537;,
 -0.00266;-2.38150;1.49633;,
 -0.75266;-2.38150;1.29537;,
 -1.30170;-2.38150;0.74633;,
 -1.50266;-2.38150;-0.00367;,
 -1.30171;-4.65065;-1.86621;,
 -0.75266;-4.65065;-2.41524;,
 -0.00266;-4.65065;-2.61621;,
 0.38557;-5.19335;-1.78864;,
 -0.00266;-5.19335;-1.89267;,
 0.66977;-5.19335;-1.50444;,
 0.77380;-2.66246;-0.00367;,
 0.66977;-2.66246;0.38456;,
 0.38557;-2.66246;0.66876;,
 -0.00266;-2.66246;0.77279;,
 -0.39089;-2.66246;0.66876;,
 -0.67510;-2.66246;0.38456;,
 -0.77912;-2.66246;-0.00367;,
 -0.67510;-5.19335;-1.50444;,
 -0.39089;-5.19335;-1.78864;,
 -0.00266;-5.19335;-1.89267;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;,
 -0.00266;-2.75829;-0.00367;;
 
 144;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 3;23,24,22;,
 4;2,1,25,26;,
 4;1,4,27,25;,
 4;4,6,28,27;,
 4;6,8,29,28;,
 4;8,10,30,29;,
 4;10,12,31,30;,
 4;12,14,32,31;,
 4;14,16,33,32;,
 4;16,18,34,33;,
 4;18,20,35,34;,
 4;20,22,36,35;,
 4;22,24,37,36;,
 4;26,25,38,39;,
 4;25,27,40,38;,
 4;27,28,41,40;,
 4;28,29,42,41;,
 4;29,30,43,42;,
 4;30,31,44,43;,
 4;31,32,45,44;,
 4;32,33,46,45;,
 4;33,34,47,46;,
 4;34,35,48,47;,
 4;35,36,49,48;,
 4;36,37,50,49;,
 4;39,38,51,52;,
 4;38,40,53,51;,
 4;40,41,54,53;,
 4;41,42,55,54;,
 4;42,43,56,55;,
 4;43,44,57,56;,
 4;44,45,58,57;,
 4;45,46,59,58;,
 4;46,47,60,59;,
 4;47,48,61,60;,
 4;48,49,62,61;,
 4;49,50,63,62;,
 4;52,51,64,65;,
 4;51,53,66,64;,
 4;53,54,67,66;,
 4;54,55,68,67;,
 4;55,56,69,68;,
 4;56,57,70,69;,
 4;57,58,71,70;,
 4;58,59,72,71;,
 4;59,60,73,72;,
 4;60,61,74,73;,
 4;61,62,75,74;,
 4;62,63,76,75;,
 4;65,64,77,78;,
 4;64,66,79,77;,
 4;66,67,80,79;,
 4;67,68,81,80;,
 4;68,69,82,81;,
 4;69,70,83,82;,
 4;70,71,84,83;,
 4;71,72,85,84;,
 4;72,73,86,85;,
 4;73,74,87,86;,
 4;74,75,88,87;,
 4;75,76,89,88;,
 4;78,77,90,91;,
 4;77,79,92,90;,
 4;79,80,93,92;,
 4;80,81,94,93;,
 4;81,82,95,94;,
 4;82,83,96,95;,
 4;83,84,97,96;,
 4;84,85,98,97;,
 4;85,86,99,98;,
 4;86,87,100,99;,
 4;87,88,101,100;,
 4;88,89,102,101;,
 4;91,90,103,104;,
 4;90,92,105,103;,
 4;92,93,106,105;,
 4;93,94,107,106;,
 4;94,95,108,107;,
 4;95,96,109,108;,
 4;96,97,110,109;,
 4;97,98,111,110;,
 4;98,99,112,111;,
 4;99,100,113,112;,
 4;100,101,114,113;,
 4;101,102,115,114;,
 4;104,103,116,117;,
 4;103,105,118,116;,
 4;105,106,119,118;,
 4;106,107,120,119;,
 4;107,108,121,120;,
 4;108,109,122,121;,
 4;109,110,123,122;,
 4;110,111,124,123;,
 4;111,112,125,124;,
 4;112,113,126,125;,
 4;113,114,127,126;,
 4;114,115,128,127;,
 4;117,116,129,130;,
 4;116,118,131,129;,
 4;118,119,132,131;,
 4;119,120,133,132;,
 4;120,121,134,133;,
 4;121,122,135,134;,
 4;122,123,136,135;,
 4;123,124,137,136;,
 4;124,125,138,137;,
 4;125,126,139,138;,
 4;126,127,140,139;,
 4;127,128,141,140;,
 4;130,129,142,143;,
 4;129,131,144,142;,
 4;131,132,145,144;,
 4;132,133,146,145;,
 4;133,134,147,146;,
 4;134,135,148,147;,
 4;135,136,149,148;,
 4;136,137,150,149;,
 4;137,138,151,150;,
 4;138,139,152,151;,
 4;139,140,153,152;,
 4;140,141,154,153;,
 3;143,142,155;,
 3;142,144,156;,
 3;144,145,157;,
 3;145,146,158;,
 3;146,147,159;,
 3;147,148,160;,
 3;148,149,161;,
 3;149,150,162;,
 3;150,151,163;,
 3;151,152,164;,
 3;152,153,165;,
 3;153,154,166;;
 
 MeshMaterialList {
  9;
  144;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.257255;0.247843;0.800000;1.000000;;
   5.000000;
   1.000000;1.000000;1.000000;;
   0.321569;0.309804;1.000000;;
  }
  Material {
   0.800000;0.768627;0.743529;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.621176;0.539608;0.053333;1.000000;;
   5.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.160000;0.128627;0.298039;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.291765;0.229020;0.530196;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.596000;0.800000;0.775200;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.775200;0.778400;0.053600;1.000000;;
   5.000000;
   0.200000;0.200000;0.200000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  151;
  -0.000001;0.881631;0.471939;,
  0.000000;0.612943;0.790127;,
  -0.412356;0.580452;0.702167;,
  -0.019226;0.589410;0.807605;,
  0.289444;0.831691;0.473827;,
  0.211193;0.969810;0.121931;,
  0.121933;0.969810;0.211191;,
  0.000000;0.969810;0.243863;,
  -0.121931;0.969810;0.211192;,
  -0.211192;0.969810;0.121930;,
  -0.289444;0.831692;0.473825;,
  0.019222;0.589409;0.807606;,
  0.412351;0.580453;0.702169;,
  0.000000;0.700654;-0.713501;,
  0.356753;0.700653;-0.617909;,
  0.513027;0.688190;-0.513028;,
  0.556647;0.742033;0.373538;,
  0.412559;0.879239;0.238190;,
  0.238192;0.879239;0.412557;,
  0.000000;0.879239;0.476381;,
  -0.238190;0.879239;0.412558;,
  -0.412558;0.879239;0.238189;,
  -0.556647;0.742034;0.373537;,
  -0.593494;0.547957;0.589499;,
  -0.356752;0.700653;-0.617911;,
  0.000001;0.490487;-0.871448;,
  0.435725;0.490486;-0.754697;,
  0.764646;0.519174;-0.381804;,
  0.736154;0.625543;0.258405;,
  0.592630;0.729191;0.342156;,
  0.342156;0.729190;0.592631;,
  0.000001;0.729191;0.684310;,
  -0.342155;0.729191;0.592630;,
  -0.592629;0.729191;0.342156;,
  -0.736154;0.625543;0.258405;,
  -0.785864;0.521664;0.332090;,
  -0.435725;0.490487;-0.754696;,
  0.000001;0.307894;-0.951421;,
  0.475711;0.307893;-0.823955;,
  0.867066;0.376290;-0.326500;,
  0.878025;0.454007;0.151492;,
  0.737617;0.523985;0.425864;,
  0.425864;0.523986;0.737617;,
  0.000000;0.523987;0.851726;,
  -0.425863;0.523986;0.737617;,
  -0.737616;0.523987;0.425865;,
  -0.878024;0.454009;0.151492;,
  -0.867066;0.376291;-0.326498;,
  -0.475712;0.307893;-0.823954;,
  0.000001;0.148228;-0.988953;,
  0.494478;0.148229;-0.856458;,
  0.889138;0.184295;-0.418891;,
  0.967703;0.238421;0.081890;,
  0.832749;0.274543;0.480787;,
  0.480788;0.274543;0.832748;,
  0.000000;0.274541;0.961575;,
  -0.480787;0.274541;0.832749;,
  -0.832748;0.274541;0.480789;,
  -0.967704;0.238419;0.081890;,
  -0.889138;0.184293;-0.418891;,
  -0.494478;0.148228;-0.856458;,
  0.000000;0.000000;-1.000000;,
  0.500001;0.000000;-0.866025;,
  0.894039;0.000000;-0.447990;,
  0.998251;0.000001;0.059120;,
  0.866026;0.000001;0.499999;,
  0.500001;0.000001;0.866025;,
  0.000000;0.000001;1.000000;,
  -0.499999;0.000001;0.866026;,
  -0.866025;0.000001;0.500000;,
  -0.998251;0.000001;0.059120;,
  -0.894039;0.000000;-0.447990;,
  -0.500000;0.000000;-0.866025;,
  0.000001;-0.148229;-0.988953;,
  0.494478;-0.148230;-0.856458;,
  0.889137;-0.184296;-0.418891;,
  0.967703;-0.238422;0.081890;,
  0.832748;-0.274545;0.480787;,
  0.480788;-0.274545;0.832747;,
  0.000000;-0.274543;0.961575;,
  -0.480786;-0.274544;0.832749;,
  -0.832748;-0.274544;0.480788;,
  -0.967703;-0.238421;0.081890;,
  -0.889138;-0.184295;-0.418890;,
  -0.494478;-0.148229;-0.856458;,
  0.000001;-0.307899;-0.951419;,
  0.475710;-0.307898;-0.823953;,
  0.867065;-0.376293;-0.326500;,
  0.878025;-0.454007;0.151491;,
  0.737619;-0.523983;0.425865;,
  0.425865;-0.523983;0.737618;,
  0.000000;-0.523985;0.851727;,
  -0.425864;-0.523984;0.737618;,
  -0.737617;-0.523985;0.425866;,
  -0.878024;-0.454009;0.151492;,
  -0.867065;-0.376294;-0.326498;,
  -0.475711;-0.307899;-0.823952;,
  0.000001;-0.490483;-0.871451;,
  0.435726;-0.490482;-0.754699;,
  0.803712;-0.570953;-0.167510;,
  0.736160;-0.625538;0.258401;,
  0.592637;-0.729184;0.342160;,
  0.342160;-0.729183;0.592638;,
  0.000000;-0.729184;0.684318;,
  -0.342160;-0.729183;0.592637;,
  -0.592637;-0.729183;0.342160;,
  -0.736161;-0.625537;0.258401;,
  -0.803712;-0.570952;-0.167511;,
  -0.435726;-0.490483;-0.754698;,
  0.000000;-0.700648;-0.713507;,
  0.356757;-0.700647;-0.617915;,
  0.513031;-0.688183;-0.513032;,
  0.556648;-0.742034;0.373536;,
  0.412556;-0.879240;0.238190;,
  0.238191;-0.879240;0.412556;,
  0.000000;-0.879240;0.476380;,
  -0.238190;-0.879240;0.412557;,
  -0.412557;-0.879240;0.238190;,
  -0.556649;-0.742034;0.373535;,
  -0.593498;-0.547957;0.589493;,
  -0.356754;-0.700647;-0.617917;,
  0.000000;-0.799977;-0.600031;,
  0.300020;-0.799975;-0.519642;,
  0.433685;-0.789832;-0.433685;,
  0.289433;-0.831695;0.473826;,
  0.211180;-0.969813;0.121925;,
  0.121925;-0.969813;0.211178;,
  0.000000;-0.969813;0.243849;,
  -0.121924;-0.969813;0.211179;,
  -0.211179;-0.969813;0.121924;,
  -0.289432;-0.831696;0.473825;,
  0.019228;-0.589410;0.807605;,
  -0.300016;-0.799975;-0.519644;,
  -0.000001;-0.881634;0.471935;,
  0.000000;0.799977;-0.600031;,
  0.300020;0.799975;-0.519642;,
  0.433685;0.789833;-0.433684;,
  0.593493;0.547957;0.589498;,
  -0.433680;0.789832;-0.433689;,
  -0.300018;0.799975;-0.519644;,
  -0.513024;0.688190;-0.513031;,
  0.688862;0.555235;0.466030;,
  -0.621233;0.477639;-0.621233;,
  0.593498;-0.547959;0.589492;,
  -0.513027;-0.688184;-0.513037;,
  0.280540;-0.532785;0.798397;,
  -0.433678;-0.789833;-0.433690;,
  0.000000;-0.612941;0.790128;,
  -0.412356;-0.580450;0.702168;,
  -0.597990;-0.533682;0.597990;,
  0.412351;-0.580451;0.702170;;
  144;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,1,12;,
  4;134,135,14,13;,
  4;135,136,15,14;,
  4;3,4,16,137;,
  4;4,5,17,16;,
  4;5,6,18,17;,
  4;6,7,19,18;,
  4;7,8,20,19;,
  4;8,9,21,20;,
  4;9,10,22,21;,
  4;10,11,23,22;,
  4;138,139,24,140;,
  4;139,134,13,24;,
  4;13,14,26,25;,
  4;14,15,27,26;,
  4;137,16,28,141;,
  4;16,17,29,28;,
  4;17,18,30,29;,
  4;18,19,31,30;,
  4;19,20,32,31;,
  4;20,21,33,32;,
  4;21,22,34,33;,
  4;22,23,35,34;,
  4;140,24,36,142;,
  4;24,13,25,36;,
  4;25,26,38,37;,
  4;26,27,39,38;,
  4;27,28,40,39;,
  4;28,29,41,40;,
  4;29,30,42,41;,
  4;30,31,43,42;,
  4;31,32,44,43;,
  4;32,33,45,44;,
  4;33,34,46,45;,
  4;34,35,47,46;,
  4;142,36,48,47;,
  4;36,25,37,48;,
  4;37,38,50,49;,
  4;38,39,51,50;,
  4;39,40,52,51;,
  4;40,41,53,52;,
  4;41,42,54,53;,
  4;42,43,55,54;,
  4;43,44,56,55;,
  4;44,45,57,56;,
  4;45,46,58,57;,
  4;46,47,59,58;,
  4;47,48,60,59;,
  4;48,37,49,60;,
  4;49,50,62,61;,
  4;50,51,63,62;,
  4;51,52,64,63;,
  4;52,53,65,64;,
  4;53,54,66,65;,
  4;54,55,67,66;,
  4;55,56,68,67;,
  4;56,57,69,68;,
  4;57,58,70,69;,
  4;58,59,71,70;,
  4;59,60,72,71;,
  4;60,49,61,72;,
  4;61,62,74,73;,
  4;62,63,75,74;,
  4;63,64,76,75;,
  4;64,65,77,76;,
  4;65,66,78,77;,
  4;66,67,79,78;,
  4;67,68,80,79;,
  4;68,69,81,80;,
  4;69,70,82,81;,
  4;70,71,83,82;,
  4;71,72,84,83;,
  4;72,61,73,84;,
  4;73,74,86,85;,
  4;74,75,87,86;,
  4;75,76,88,87;,
  4;76,77,89,88;,
  4;77,78,90,89;,
  4;78,79,91,90;,
  4;79,80,92,91;,
  4;80,81,93,92;,
  4;81,82,94,93;,
  4;82,83,95,94;,
  4;83,84,96,95;,
  4;84,73,85,96;,
  4;85,86,98,97;,
  4;86,87,99,98;,
  4;87,88,100,99;,
  4;88,89,101,100;,
  4;89,90,102,101;,
  4;90,91,103,102;,
  4;91,92,104,103;,
  4;92,93,105,104;,
  4;93,94,106,105;,
  4;94,95,107,106;,
  4;95,96,108,107;,
  4;96,85,97,108;,
  4;97,98,110,109;,
  4;98,99,111,110;,
  4;99,100,112,143;,
  4;100,101,113,112;,
  4;101,102,114,113;,
  4;102,103,115,114;,
  4;103,104,116,115;,
  4;104,105,117,116;,
  4;105,106,118,117;,
  4;106,107,119,118;,
  4;107,108,120,144;,
  4;108,97,109,120;,
  4;109,110,122,121;,
  4;110,111,123,122;,
  4;143,112,124,145;,
  4;112,113,125,124;,
  4;113,114,126,125;,
  4;114,115,127,126;,
  4;115,116,128,127;,
  4;116,117,129,128;,
  4;117,118,130,129;,
  4;118,119,131,130;,
  4;144,120,132,146;,
  4;120,109,121,132;,
  3;147,148,133;,
  3;148,149,133;,
  3;145,124,133;,
  3;124,125,133;,
  3;125,126,133;,
  3;126,127,133;,
  3;127,128,133;,
  3;128,129,133;,
  3;129,130,133;,
  3;130,131,133;,
  3;131,150,133;,
  3;150,147,133;;
 }
 MeshTextureCoords {
  167;
  0.041670;0.000000;,
  0.083330;0.083330;,
  0.000000;0.083330;,
  0.125000;0.000000;,
  0.166670;0.083330;,
  0.208330;0.000000;,
  0.250000;0.083330;,
  0.291670;0.000000;,
  0.333330;0.083330;,
  0.375000;0.000000;,
  0.416670;0.083330;,
  0.458330;0.000000;,
  0.500000;0.083330;,
  0.541670;0.000000;,
  0.583330;0.083330;,
  0.625000;0.000000;,
  0.666670;0.083330;,
  0.708330;0.000000;,
  0.750000;0.083330;,
  0.791670;0.000000;,
  0.833330;0.083330;,
  0.875000;0.000000;,
  0.916670;0.083330;,
  0.958330;0.000000;,
  1.000000;0.083330;,
  0.083330;0.166670;,
  0.000000;0.166670;,
  0.166670;0.166670;,
  0.250000;0.166670;,
  0.333330;0.166670;,
  0.416670;0.166670;,
  0.500000;0.166670;,
  0.583330;0.166670;,
  0.666670;0.166670;,
  0.750000;0.166670;,
  0.833330;0.166670;,
  0.916670;0.166670;,
  1.000000;0.166670;,
  0.083330;0.250000;,
  0.000000;0.250000;,
  0.166670;0.250000;,
  0.250000;0.250000;,
  0.333330;0.250000;,
  0.416670;0.250000;,
  0.500000;0.250000;,
  0.583330;0.250000;,
  0.666670;0.250000;,
  0.750000;0.250000;,
  0.833330;0.250000;,
  0.916670;0.250000;,
  1.000000;0.250000;,
  0.083330;0.333330;,
  0.000000;0.333330;,
  0.166670;0.333330;,
  0.250000;0.333330;,
  0.333330;0.333330;,
  0.416670;0.333330;,
  0.500000;0.333330;,
  0.583330;0.333330;,
  0.666670;0.333330;,
  0.750000;0.333330;,
  0.833330;0.333330;,
  0.916670;0.333330;,
  1.000000;0.333330;,
  0.083330;0.416670;,
  0.000000;0.416670;,
  0.166670;0.416670;,
  0.250000;0.416670;,
  0.333330;0.416670;,
  0.416670;0.416670;,
  0.500000;0.416670;,
  0.583330;0.416670;,
  0.666670;0.416670;,
  0.750000;0.416670;,
  0.833330;0.416670;,
  0.916670;0.416670;,
  1.000000;0.416670;,
  0.083330;0.500000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.250000;0.500000;,
  0.333330;0.500000;,
  0.416670;0.500000;,
  0.500000;0.500000;,
  0.583330;0.500000;,
  0.666670;0.500000;,
  0.750000;0.500000;,
  0.833330;0.500000;,
  0.916670;0.500000;,
  1.000000;0.500000;,
  0.083330;0.583330;,
  0.000000;0.583330;,
  0.166670;0.583330;,
  0.250000;0.583330;,
  0.333330;0.583330;,
  0.416670;0.583330;,
  0.500000;0.583330;,
  0.583330;0.583330;,
  0.666670;0.583330;,
  0.750000;0.583330;,
  0.833330;0.583330;,
  0.916670;0.583330;,
  1.000000;0.583330;,
  0.083330;0.666670;,
  0.000000;0.666670;,
  0.166670;0.666670;,
  0.250000;0.666670;,
  0.333330;0.666670;,
  0.416670;0.666670;,
  0.500000;0.666670;,
  0.583330;0.666670;,
  0.666670;0.666670;,
  0.750000;0.666670;,
  0.833330;0.666670;,
  0.916670;0.666670;,
  1.000000;0.666670;,
  0.083330;0.750000;,
  0.000000;0.750000;,
  0.166670;0.750000;,
  0.250000;0.750000;,
  0.333330;0.750000;,
  0.416670;0.750000;,
  0.500000;0.750000;,
  0.583330;0.750000;,
  0.666670;0.750000;,
  0.750000;0.750000;,
  0.833330;0.750000;,
  0.916670;0.750000;,
  1.000000;0.750000;,
  0.083330;0.833330;,
  0.000000;0.833330;,
  0.166670;0.833330;,
  0.250000;0.833330;,
  0.333330;0.833330;,
  0.416670;0.833330;,
  0.500000;0.833330;,
  0.583330;0.833330;,
  0.666670;0.833330;,
  0.750000;0.833330;,
  0.833330;0.833330;,
  0.916670;0.833330;,
  1.000000;0.833330;,
  0.083330;0.916670;,
  0.000000;0.916670;,
  0.166670;0.916670;,
  0.250000;0.916670;,
  0.333330;0.916670;,
  0.416670;0.916670;,
  0.500000;0.916670;,
  0.583330;0.916670;,
  0.666670;0.916670;,
  0.750000;0.916670;,
  0.833330;0.916670;,
  0.916670;0.916670;,
  1.000000;0.916670;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.708330;1.000000;,
  0.791670;1.000000;,
  0.875000;1.000000;,
  0.958330;1.000000;;
 }
}
