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
 66;
 0.00000;0.00000;-110.00000;,
 0.00000;27.50000;-82.50000;,
 31.57138;27.50000;-76.22006;,
 50.33794;-0.92010;-107.80130;,
 58.33631;27.50000;-58.33631;,
 89.99032;-1.54847;-88.24660;,
 76.22006;27.50000;-31.57138;,
 104.56170;-0.55946;-45.94049;,
 82.50000;27.50000;0.00000;,
 110.00000;0.00000;0.00000;,
 76.22006;27.50000;31.57139;,
 105.86620;-0.08265;41.68996;,
 58.33631;27.50000;58.33631;,
 87.87496;0.95168;86.12155;,
 31.57139;27.50000;76.22006;,
 48.79233;0.15287;103.00576;,
 0.00001;27.50000;82.50000;,
 0.00002;0.00000;110.00000;,
 -31.57137;27.50000;76.22007;,
 -44.64088;0.74880;106.83691;,
 -58.33629;27.50000;58.33633;,
 -85.30502;1.09503;85.23029;,
 -76.22006;27.50000;31.57139;,
 -104.41798;0.71231;47.03288;,
 -82.50000;27.50000;-0.00000;,
 -110.00000;0.00000;-0.00000;,
 -76.22006;27.50000;-31.57140;,
 -104.09691;-0.95819;-49.00772;,
 -58.33629;27.50000;-58.33633;,
 -83.13434;-0.83696;-83.95912;,
 -31.57135;27.50000;-76.22008;,
 -42.09513;0.00000;-101.62677;,
 0.00000;47.83247;-55.00000;,
 21.04759;47.83247;-50.81338;,
 38.89087;47.83247;-38.89087;,
 50.81338;47.83247;-21.04759;,
 55.00000;47.83247;0.00000;,
 50.81337;47.83247;21.04759;,
 38.89087;47.83247;38.89087;,
 21.04759;47.83247;50.81337;,
 0.00001;47.83247;55.00000;,
 -21.04758;47.83247;50.81338;,
 -38.89086;47.83247;38.89089;,
 -50.81337;47.83247;21.04760;,
 -55.00000;47.83247;-0.00000;,
 -50.81337;47.83247;-21.04760;,
 -38.89086;47.83247;-38.89089;,
 -21.04756;47.83247;-50.81338;,
 0.00000;68.17501;-27.50000;,
 10.52380;68.17501;-25.40669;,
 19.44544;68.17501;-19.44544;,
 25.40669;68.17501;-10.52379;,
 27.50000;68.17501;0.00000;,
 25.40669;68.17501;10.52380;,
 19.44544;68.17501;19.44544;,
 10.52380;68.17501;25.40669;,
 0.00000;68.17501;27.50000;,
 -10.52379;68.17501;25.40669;,
 -19.44543;68.17501;19.44544;,
 -25.40669;68.17501;10.52380;,
 -27.50000;68.17501;-0.00000;,
 -25.40669;68.17501;-10.52380;,
 -19.44543;68.17501;-19.44544;,
 -10.52378;68.17501;-25.40669;,
 0.00000;79.30130;0.00000;,
 0.00000;0.00000;0.00000;;
 
 80;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;29,28,30,31;,
 4;31,30,1,0;,
 4;1,32,33,2;,
 4;2,33,34,4;,
 4;4,34,35,6;,
 4;6,35,36,8;,
 4;8,36,37,10;,
 4;10,37,38,12;,
 4;12,38,39,14;,
 4;14,39,40,16;,
 4;16,40,41,18;,
 4;18,41,42,20;,
 4;20,42,43,22;,
 4;22,43,44,24;,
 4;24,44,45,26;,
 4;26,45,46,28;,
 4;28,46,47,30;,
 4;30,47,32,1;,
 4;32,48,49,33;,
 4;33,49,50,34;,
 4;34,50,51,35;,
 4;35,51,52,36;,
 4;36,52,53,37;,
 4;37,53,54,38;,
 4;38,54,55,39;,
 4;39,55,56,40;,
 4;40,56,57,41;,
 4;41,57,58,42;,
 4;42,58,59,43;,
 4;43,59,60,44;,
 4;44,60,61,45;,
 4;45,61,62,46;,
 4;46,62,63,47;,
 4;47,63,48,32;,
 3;48,64,49;,
 3;49,64,50;,
 3;50,64,51;,
 3;51,64,52;,
 3;52,64,53;,
 3;53,64,54;,
 3;54,64,55;,
 3;55,64,56;,
 3;56,64,57;,
 3;57,64,58;,
 3;58,64,59;,
 3;59,64,60;,
 3;60,64,61;,
 3;61,64,62;,
 3;62,64,63;,
 3;63,64,48;,
 3;65,0,3;,
 3;65,3,5;,
 3;65,5,7;,
 3;65,7,9;,
 3;65,9,11;,
 3;65,11,13;,
 3;65,13,15;,
 3;65,15,17;,
 3;65,17,19;,
 3;65,19,21;,
 3;65,21,23;,
 3;65,23,25;,
 3;65,25,27;,
 3;65,27,29;,
 3;65,29,31;,
 3;65,31,0;;
 
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
   0.702745;0.401569;0.100392;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\field001.jpg";
   }
  }
 }
 MeshNormals {
  82;
  -0.024308;0.719488;-0.694079;,
  0.199032;0.774273;-0.600739;,
  0.433770;0.804362;-0.406013;,
  0.624949;0.753744;-0.203245;,
  0.690913;0.722918;-0.005378;,
  0.623566;0.756387;0.197598;,
  0.429819;0.797360;0.423641;,
  0.205561;0.755756;0.621753;,
  0.015508;0.726402;0.687095;,
  -0.200926;0.769288;0.606486;,
  -0.427665;0.799703;0.421399;,
  -0.614258;0.761334;0.207506;,
  -0.691900;0.721958;-0.007076;,
  -0.624008;0.745778;-0.233298;,
  -0.445287;0.759438;-0.474313;,
  -0.237731;0.721833;-0.649954;,
  -0.012182;0.763473;-0.645725;,
  0.213408;0.789632;-0.575272;,
  0.427073;0.804263;-0.413244;,
  0.587757;0.779777;-0.215615;,
  0.644018;0.765006;-0.002696;,
  0.587051;0.781085;0.212785;,
  0.425085;0.800755;0.422012;,
  0.216756;0.780713;0.586093;,
  0.007775;0.766636;0.642035;,
  -0.214376;0.787223;0.578207;,
  -0.424019;0.801908;0.420894;,
  -0.582199;0.783361;0.217692;,
  -0.644537;0.764565;-0.003547;,
  -0.587248;0.775845;-0.230661;,
  -0.433093;0.782377;-0.447568;,
  -0.233118;0.764576;-0.600900;,
  0.000000;0.804017;-0.594607;,
  0.227546;0.804017;-0.549345;,
  0.420451;0.804017;-0.420451;,
  0.549345;0.804017;-0.227546;,
  0.594607;0.804017;0.000000;,
  0.549345;0.804017;0.227546;,
  0.420451;0.804017;0.420451;,
  0.227546;0.804017;0.549345;,
  0.000000;0.804017;0.594607;,
  -0.227546;0.804017;0.549345;,
  -0.420450;0.804017;0.420451;,
  -0.549345;0.804017;0.227546;,
  -0.594607;0.804017;0.000000;,
  -0.549345;0.804017;-0.227546;,
  -0.420450;0.804017;-0.420451;,
  -0.227546;0.804017;-0.549345;,
  0.000000;0.872543;-0.488537;,
  0.186955;0.872543;-0.451349;,
  0.345448;0.872543;-0.345448;,
  0.451349;0.872543;-0.186955;,
  0.488537;0.872543;0.000000;,
  0.451349;0.872543;0.186955;,
  0.345448;0.872543;0.345448;,
  0.186955;0.872543;0.451349;,
  0.000000;0.872543;0.488537;,
  -0.186955;0.872543;0.451349;,
  -0.345448;0.872543;0.345448;,
  -0.451349;0.872543;0.186955;,
  -0.488537;0.872543;0.000000;,
  -0.451349;0.872543;-0.186955;,
  -0.345448;0.872543;-0.345448;,
  -0.186955;0.872543;-0.451349;,
  0.000000;1.000000;0.000000;,
  -0.001323;-0.999984;0.005558;,
  -0.009138;-0.999958;0.000000;,
  -0.017288;-0.999851;0.000461;,
  -0.006014;-0.999917;0.011413;,
  0.002136;-0.999853;0.017039;,
  -0.000000;-0.999987;0.005097;,
  -0.004289;-0.999951;0.008910;,
  0.004460;-0.999969;0.006499;,
  0.010315;-0.999941;-0.003402;,
  -0.006820;-0.999977;0.000000;,
  -0.013393;-0.999909;0.001412;,
  -0.005949;-0.999959;0.006893;,
  -0.000942;-0.999914;0.013052;,
  -0.000000;-0.999850;0.017346;,
  0.004226;-0.999935;0.010575;,
  0.012878;-0.999913;-0.002784;,
  0.008653;-0.999956;-0.003584;;
  80;
  4;0,16,17,1;,
  4;1,17,18,2;,
  4;2,18,19,3;,
  4;3,19,20,4;,
  4;4,20,21,5;,
  4;5,21,22,6;,
  4;6,22,23,7;,
  4;7,23,24,8;,
  4;8,24,25,9;,
  4;9,25,26,10;,
  4;10,26,27,11;,
  4;11,27,28,12;,
  4;12,28,29,13;,
  4;13,29,30,14;,
  4;14,30,31,15;,
  4;15,31,16,0;,
  4;16,32,33,17;,
  4;17,33,34,18;,
  4;18,34,35,19;,
  4;19,35,36,20;,
  4;20,36,37,21;,
  4;21,37,38,22;,
  4;22,38,39,23;,
  4;23,39,40,24;,
  4;24,40,41,25;,
  4;25,41,42,26;,
  4;26,42,43,27;,
  4;27,43,44,28;,
  4;28,44,45,29;,
  4;29,45,46,30;,
  4;30,46,47,31;,
  4;31,47,32,16;,
  4;32,48,49,33;,
  4;33,49,50,34;,
  4;34,50,51,35;,
  4;35,51,52,36;,
  4;36,52,53,37;,
  4;37,53,54,38;,
  4;38,54,55,39;,
  4;39,55,56,40;,
  4;40,56,57,41;,
  4;41,57,58,42;,
  4;42,58,59,43;,
  4;43,59,60,44;,
  4;44,60,61,45;,
  4;45,61,62,46;,
  4;46,62,63,47;,
  4;47,63,48,32;,
  3;48,64,49;,
  3;49,64,50;,
  3;50,64,51;,
  3;51,64,52;,
  3;52,64,53;,
  3;53,64,54;,
  3;54,64,55;,
  3;55,64,56;,
  3;56,64,57;,
  3;57,64,58;,
  3;58,64,59;,
  3;59,64,60;,
  3;60,64,61;,
  3;61,64,62;,
  3;62,64,63;,
  3;63,64,48;,
  3;65,66,67;,
  3;65,67,68;,
  3;65,68,69;,
  3;65,69,70;,
  3;65,70,71;,
  3;65,71,72;,
  3;65,72,73;,
  3;65,73,74;,
  3;65,74,75;,
  3;65,75,76;,
  3;65,76,77;,
  3;65,77,78;,
  3;65,78,79;,
  3;65,79,80;,
  3;65,80,81;,
  3;65,81,66;;
 }
 MeshTextureCoords {
  66;
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.643506;0.153545;,
  0.728809;0.009994;,
  0.765165;0.234835;,
  0.909047;0.098879;,
  0.846455;0.356494;,
  0.975280;0.291180;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.846455;0.643506;,
  0.981210;0.689500;,
  0.765165;0.765165;,
  0.899432;0.891462;,
  0.643506;0.846455;,
  0.721783;0.968208;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.356494;0.846455;,
  0.297087;0.985622;,
  0.234835;0.765165;,
  0.112250;0.887410;,
  0.153545;0.643506;,
  0.025373;0.713786;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.153545;0.356494;,
  0.026832;0.277238;,
  0.234835;0.234835;,
  0.122117;0.118368;,
  0.356494;0.153545;,
  0.308659;0.038060;,
  0.500000;0.250000;,
  0.595671;0.269030;,
  0.676777;0.323223;,
  0.730970;0.404329;,
  0.750000;0.500000;,
  0.730970;0.595671;,
  0.676777;0.676777;,
  0.595671;0.730970;,
  0.500000;0.750000;,
  0.404329;0.730970;,
  0.323223;0.676777;,
  0.269030;0.595671;,
  0.250000;0.500000;,
  0.269030;0.404329;,
  0.323223;0.323223;,
  0.404329;0.269030;,
  0.500000;0.375000;,
  0.547835;0.384515;,
  0.588388;0.411612;,
  0.615485;0.452165;,
  0.625000;0.500000;,
  0.615485;0.547835;,
  0.588388;0.588388;,
  0.547835;0.615485;,
  0.500000;0.625000;,
  0.452165;0.615485;,
  0.411612;0.588388;,
  0.384515;0.547835;,
  0.375000;0.500000;,
  0.384515;0.452165;,
  0.411612;0.411612;,
  0.452165;0.384515;,
  0.500000;0.500000;,
  0.500000;0.500000;;
 }
}
