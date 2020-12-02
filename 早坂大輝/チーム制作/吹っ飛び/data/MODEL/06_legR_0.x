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
 126;
 0.00000;-0.08128;-2.81250;,
 1.40625;-0.08128;-2.43570;,
 1.40625;-25.39377;-2.43570;,
 0.00000;-25.39377;-2.81250;,
 2.43570;-0.08128;-1.40625;,
 2.43570;-25.39377;-1.40625;,
 2.81250;-0.08128;0.00000;,
 2.81250;-25.39377;0.00000;,
 2.43570;-0.08128;1.40625;,
 2.43570;-25.39377;1.40625;,
 1.40625;-0.08128;2.43570;,
 1.40625;-25.39377;2.43570;,
 0.00000;-0.08128;2.81250;,
 0.00000;-25.39377;2.81250;,
 -1.40625;-0.08128;2.43570;,
 -1.40625;-25.39377;2.43570;,
 -2.43570;-0.08128;1.40625;,
 -2.43570;-25.39377;1.40625;,
 -2.81250;-0.08128;0.00000;,
 -2.81250;-25.39377;0.00000;,
 -2.43570;-0.08128;-1.40625;,
 -2.43570;-25.39377;-1.40625;,
 -1.40625;-0.08128;-2.43570;,
 -1.40625;-25.39377;-2.43570;,
 0.00000;-0.08128;-2.81250;,
 0.00000;-25.39377;-2.81250;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-0.08128;-0.00000;,
 0.00000;-25.49312;-2.80767;,
 1.40384;-25.49312;-2.43152;,
 1.29698;-26.56757;-2.24643;,
 0.00000;-26.56757;-2.59395;,
 2.43152;-25.49312;-1.40384;,
 2.24643;-26.56757;-1.29698;,
 2.80767;-25.49312;0.00000;,
 2.59395;-26.56757;0.00000;,
 2.43152;-25.49312;1.40384;,
 2.24643;-26.56757;1.29698;,
 1.40384;-25.49312;2.43152;,
 1.29698;-26.56757;2.24643;,
 0.00000;-25.49312;2.80767;,
 0.00000;-26.56757;2.59395;,
 -1.40384;-25.49312;2.43152;,
 -1.29698;-26.56757;2.24643;,
 -2.43152;-25.49312;1.40384;,
 -2.24643;-26.56757;1.29698;,
 -2.80767;-25.49312;0.00000;,
 -2.59395;-26.56757;0.00000;,
 -2.43152;-25.49312;-1.40384;,
 -2.24643;-26.56757;-1.29698;,
 -1.40384;-25.49312;-2.43152;,
 -1.29698;-26.56757;-2.24643;,
 0.00000;-25.49312;-2.80767;,
 0.00000;-26.56757;-2.59395;,
 0.99266;-27.47845;-1.71934;,
 0.00000;-27.47845;-1.98533;,
 1.71934;-27.47845;-0.99266;,
 1.98533;-27.47845;0.00000;,
 1.71934;-27.47845;0.99266;,
 0.99266;-27.47845;1.71934;,
 0.00000;-27.47845;1.98533;,
 -0.99266;-27.47845;1.71934;,
 -1.71934;-27.47845;0.99266;,
 -1.98533;-27.47845;0.00000;,
 -1.71934;-27.47845;-0.99266;,
 -0.99266;-27.47845;-1.71934;,
 0.00000;-27.47845;-1.98533;,
 0.53723;-28.08708;-0.93050;,
 0.00000;-28.08708;-1.07445;,
 0.93050;-28.08708;-0.53723;,
 1.07445;-28.08708;0.00000;,
 0.93050;-28.08708;0.53723;,
 0.53723;-28.08708;0.93050;,
 0.00000;-28.08708;1.07445;,
 -0.53723;-28.08708;0.93050;,
 -0.93050;-28.08708;0.53723;,
 -1.07445;-28.08708;0.00000;,
 -0.93050;-28.08708;-0.53723;,
 -0.53723;-28.08708;-0.93050;,
 0.00000;-28.08708;-1.07445;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 0.00000;-28.30079;-0.00000;,
 1.40625;-25.39377;-2.43570;,
 0.00000;-25.39377;-2.81250;,
 1.40625;-25.39377;-2.43570;,
 2.43570;-25.39377;-1.40625;,
 2.81250;-25.39377;0.00000;,
 2.43570;-25.39377;-1.40625;,
 2.43570;-25.39377;1.40625;,
 2.81250;-25.39377;0.00000;,
 1.40625;-25.39377;2.43570;,
 2.43570;-25.39377;1.40625;,
 0.00000;-25.39377;2.81250;,
 1.40625;-25.39377;2.43570;,
 -1.40625;-25.39377;2.43570;,
 0.00000;-25.39377;2.81250;,
 -2.43570;-25.39377;1.40625;,
 -1.40625;-25.39377;2.43570;,
 -2.81250;-25.39377;0.00000;,
 -2.43570;-25.39377;1.40625;,
 -2.43570;-25.39377;-1.40625;,
 -2.81250;-25.39377;0.00000;,
 -1.40625;-25.39377;-2.43570;,
 -2.43570;-25.39377;-1.40625;,
 0.00000;-25.39377;-2.81250;,
 -1.40625;-25.39377;-2.43570;;
 
 84;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 3;26,1,0;,
 3;27,4,1;,
 3;28,6,4;,
 3;29,8,6;,
 3;30,10,8;,
 3;31,12,10;,
 3;32,14,12;,
 3;33,16,14;,
 3;34,18,16;,
 3;35,20,18;,
 3;36,22,20;,
 3;37,24,22;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;41,40,64,65;,
 4;40,43,66,64;,
 4;43,45,67,66;,
 4;45,47,68,67;,
 4;47,49,69,68;,
 4;49,51,70,69;,
 4;51,53,71,70;,
 4;53,55,72,71;,
 4;55,57,73,72;,
 4;57,59,74,73;,
 4;59,61,75,74;,
 4;61,63,76,75;,
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
 3;78,77,90;,
 3;77,79,91;,
 3;79,80,92;,
 3;80,81,93;,
 3;81,82,94;,
 3;82,83,95;,
 3;83,84,96;,
 3;84,85,97;,
 3;85,86,98;,
 3;86,87,99;,
 3;87,88,100;,
 3;88,89,101;,
 4;102,39,38,103;,
 4;39,104,105,42;,
 4;106,44,42,107;,
 4;108,46,44,109;,
 4;110,48,46,111;,
 4;112,50,48,113;,
 4;114,52,50,115;,
 4;116,54,52,117;,
 4;118,56,54,119;,
 4;120,58,56,121;,
 4;122,60,58,123;,
 4;124,62,60,125;;
 
 MeshMaterialList {
  1;
  84;
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
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.138039;0.138039;0.138039;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  74;
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.500000;0.000000;-0.866025;,
  0.866025;0.000000;-0.500000;,
  1.000000;0.000000;0.000000;,
  0.866025;0.000000;0.500000;,
  0.500000;0.000000;0.866025;,
  0.000000;0.000000;1.000000;,
  -0.500000;0.000000;0.866026;,
  -0.866025;0.000000;0.500000;,
  -1.000000;0.000000;0.000000;,
  -0.866026;0.000000;-0.499999;,
  -0.500000;0.000000;-0.866025;,
  -0.000000;-0.122181;-0.992508;,
  0.496254;-0.122181;-0.859537;,
  0.859537;-0.122181;-0.496254;,
  0.992508;-0.122181;0.000000;,
  0.859537;-0.122181;0.496254;,
  0.496254;-0.122181;0.859537;,
  0.000000;-0.122181;0.992508;,
  -0.496254;-0.122182;0.859537;,
  -0.859537;-0.122182;0.496254;,
  -0.992508;-0.122181;0.000000;,
  -0.859537;-0.122182;-0.496253;,
  -0.496255;-0.122181;-0.859537;,
  -0.000000;-0.383526;-0.923530;,
  0.461765;-0.383525;-0.799801;,
  0.799801;-0.383525;-0.461765;,
  0.923530;-0.383525;0.000000;,
  0.799801;-0.383525;0.461765;,
  0.461766;-0.383525;0.799800;,
  0.000000;-0.383525;0.923530;,
  -0.461765;-0.383525;0.799801;,
  -0.799800;-0.383525;0.461766;,
  -0.923530;-0.383526;0.000001;,
  -0.799801;-0.383525;-0.461765;,
  -0.461766;-0.383525;-0.799800;,
  -0.000000;-0.708038;-0.706175;,
  0.353088;-0.708038;-0.611565;,
  0.611565;-0.708038;-0.353087;,
  0.706175;-0.708038;0.000000;,
  0.611565;-0.708038;0.353088;,
  0.353088;-0.708038;0.611565;,
  0.000000;-0.708038;0.706174;,
  -0.353087;-0.708038;0.611565;,
  -0.611565;-0.708038;0.353088;,
  -0.706175;-0.708038;0.000000;,
  -0.611565;-0.708038;-0.353087;,
  -0.353088;-0.708037;-0.611565;,
  -0.000000;-0.924245;-0.381800;,
  0.190900;-0.924245;-0.330648;,
  0.330648;-0.924245;-0.190900;,
  0.381800;-0.924245;0.000000;,
  0.330648;-0.924245;0.190900;,
  0.190900;-0.924245;0.330648;,
  0.000000;-0.924245;0.381800;,
  -0.190900;-0.924245;0.330648;,
  -0.330648;-0.924245;0.190900;,
  -0.381800;-0.924245;0.000000;,
  -0.330648;-0.924245;-0.190900;,
  -0.190900;-0.924245;-0.330648;,
  0.000000;-1.000000;0.000000;,
  0.258535;-0.046867;-0.964864;,
  0.706330;-0.046869;-0.706330;,
  0.964864;-0.046867;-0.258535;,
  0.964864;-0.046867;0.258535;,
  0.706330;-0.046869;0.706330;,
  0.258535;-0.046867;0.964864;,
  -0.258535;-0.046869;0.964864;,
  -0.706329;-0.046871;0.706330;,
  -0.964864;-0.046866;0.258535;,
  -0.964864;-0.046869;-0.258534;,
  -0.706330;-0.046870;-0.706329;,
  -0.258535;-0.046866;-0.964864;;
  84;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,1,1,12;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;13,14,26,25;,
  4;14,15,27,26;,
  4;15,16,28,27;,
  4;16,17,29,28;,
  4;17,18,30,29;,
  4;18,19,31,30;,
  4;19,20,32,31;,
  4;20,21,33,32;,
  4;21,22,34,33;,
  4;22,23,35,34;,
  4;23,24,36,35;,
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
  4;35,36,48,47;,
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
  3;49,50,61;,
  3;50,51,61;,
  3;51,52,61;,
  3;52,53,61;,
  3;53,54,61;,
  3;54,55,61;,
  3;55,56,61;,
  3;56,57,61;,
  3;57,58,61;,
  3;58,59,61;,
  3;59,60,61;,
  3;60,49,61;,
  4;62,14,13,62;,
  4;14,63,63,15;,
  4;64,16,15,64;,
  4;65,17,16,65;,
  4;66,18,17,66;,
  4;67,19,18,67;,
  4;68,20,19,68;,
  4;69,21,20,69;,
  4;70,22,21,70;,
  4;71,23,22,71;,
  4;72,24,23,72;,
  4;73,13,24,73;;
 }
 MeshTextureCoords {
  126;
  0.000000;0.000000;,
  0.083333;0.000000;,
  0.083333;1.000000;,
  0.000000;1.000000;,
  0.166667;0.000000;,
  0.166667;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.333333;0.000000;,
  0.333333;1.000000;,
  0.416667;0.000000;,
  0.416667;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.583333;0.000000;,
  0.583333;1.000000;,
  0.666667;0.000000;,
  0.666667;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.833333;0.000000;,
  0.833333;1.000000;,
  0.916667;0.000000;,
  0.916667;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.041667;0.000000;,
  0.125000;0.000000;,
  0.208333;0.000000;,
  0.291667;0.000000;,
  0.375000;0.000000;,
  0.458333;0.000000;,
  0.541667;0.000000;,
  0.625000;0.000000;,
  0.708333;0.000000;,
  0.791667;0.000000;,
  0.875000;0.000000;,
  0.958333;0.000000;,
  0.000000;0.500000;,
  0.083333;0.500000;,
  0.083333;0.625000;,
  0.000000;0.625000;,
  0.166667;0.500000;,
  0.166667;0.625000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.333333;0.500000;,
  0.333333;0.625000;,
  0.416667;0.500000;,
  0.416667;0.625000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.583333;0.500000;,
  0.583333;0.625000;,
  0.666667;0.500000;,
  0.666667;0.625000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.833333;0.500000;,
  0.833333;0.625000;,
  0.916667;0.500000;,
  0.916667;0.625000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  0.083333;0.750000;,
  0.000000;0.750000;,
  0.166667;0.750000;,
  0.250000;0.750000;,
  0.333333;0.750000;,
  0.416667;0.750000;,
  0.500000;0.750000;,
  0.583333;0.750000;,
  0.666667;0.750000;,
  0.750000;0.750000;,
  0.833333;0.750000;,
  0.916667;0.750000;,
  1.000000;0.750000;,
  0.083333;0.875000;,
  0.000000;0.875000;,
  0.166667;0.875000;,
  0.250000;0.875000;,
  0.333333;0.875000;,
  0.416667;0.875000;,
  0.500000;0.875000;,
  0.583333;0.875000;,
  0.666667;0.875000;,
  0.750000;0.875000;,
  0.833333;0.875000;,
  0.916667;0.875000;,
  1.000000;0.875000;,
  0.041667;1.000000;,
  0.125000;1.000000;,
  0.208333;1.000000;,
  0.291667;1.000000;,
  0.375000;1.000000;,
  0.458333;1.000000;,
  0.541667;1.000000;,
  0.625000;1.000000;,
  0.708333;1.000000;,
  0.791667;1.000000;,
  0.875000;1.000000;,
  0.958333;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
