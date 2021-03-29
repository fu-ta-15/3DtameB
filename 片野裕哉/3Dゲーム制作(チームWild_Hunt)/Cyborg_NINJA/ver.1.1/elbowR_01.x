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
 2.81630;-0.00674;0.00234;,
 2.72047;-0.37070;-0.56503;,
 2.72047;-0.00674;-0.65279;,
 2.81630;-0.00674;0.00234;,
 2.72047;-0.63714;-0.32523;,
 2.81630;-0.00674;0.00234;,
 2.72047;-0.73466;0.00234;,
 2.81630;-0.00674;0.00234;,
 2.72047;-0.63714;0.32991;,
 2.81630;-0.00674;0.00234;,
 4.07880;-0.37070;1.39647;,
 2.81630;-0.00674;0.00234;,
 4.07880;-0.00674;1.48423;,
 2.81630;-0.00674;0.00234;,
 4.07880;0.35722;1.39647;,
 2.81630;-0.00674;0.00234;,
 2.72047;0.62367;0.32991;,
 2.81630;-0.00674;0.00234;,
 2.72047;0.72119;0.00234;,
 2.81630;-0.00674;0.00234;,
 2.72047;0.62367;-0.32523;,
 2.81630;-0.00674;0.00234;,
 2.72047;0.35722;-0.56503;,
 2.81630;-0.00674;0.00234;,
 2.72047;-0.00674;-0.65279;,
 2.43950;-0.70986;-1.09373;,
 2.43950;-0.00674;-1.26328;,
 2.43950;-1.22459;-0.63047;,
 2.43950;-1.41299;0.00234;,
 3.65735;-1.22459;1.46191;,
 3.65735;-0.70986;1.92517;,
 3.65735;-0.00674;2.09473;,
 3.65735;0.69639;1.92517;,
 3.65735;1.21111;1.46191;,
 2.43950;1.39951;0.00234;,
 2.43950;1.21111;-0.63047;,
 2.43950;0.69639;-1.09373;,
 2.43950;-0.00674;-1.26328;,
 1.99254;-1.00111;-1.54773;,
 1.99254;-0.00674;-1.78752;,
 1.99254;-1.72904;-0.89260;,
 1.99254;-1.99547;0.00234;,
 2.98691;-1.72904;1.72404;,
 2.98691;-1.00111;2.37917;,
 2.98691;-0.00674;2.61896;,
 2.98691;0.98763;2.37917;,
 2.98691;1.71555;1.72404;,
 1.99254;1.98200;0.00234;,
 1.99254;1.71556;-0.89259;,
 1.99254;0.98763;-1.54773;,
 1.99254;-0.00674;-1.78752;,
 1.41005;-1.22459;-1.89610;,
 1.41005;-0.00674;-2.18979;,
 1.41005;-2.11611;-1.09373;,
 1.41005;-2.44244;0.00234;,
 2.11318;-2.11611;1.92517;,
 2.11318;-1.22459;2.72754;,
 2.11318;-0.00674;3.02123;,
 2.11318;1.21111;2.72754;,
 2.11318;2.10264;1.92517;,
 1.41005;2.42896;0.00234;,
 1.41005;2.10264;-1.09373;,
 1.41005;1.21111;-1.89610;,
 1.41005;-0.00674;-2.18979;,
 0.73173;-1.36507;-2.11510;,
 0.73173;-0.00674;-2.44266;,
 0.73173;-2.35944;-1.22016;,
 0.73173;-2.72340;0.00234;,
 1.09569;-2.35944;2.05160;,
 1.09569;-1.36507;2.94654;,
 1.09569;-0.00674;3.27410;,
 1.09569;1.35160;2.94654;,
 1.09569;2.34597;2.05160;,
 0.73173;2.70993;0.00234;,
 0.73173;2.34597;-1.22016;,
 0.73173;1.35160;-2.11510;,
 0.73173;-0.00674;-2.44266;,
 0.00380;-1.41299;-2.18978;,
 0.00380;-0.00674;-2.52891;,
 0.00380;-2.44244;-1.26328;,
 0.00380;-2.81924;0.00234;,
 0.00380;-2.44244;2.09473;,
 0.00380;-1.41299;3.02123;,
 0.00380;-0.00674;3.36035;,
 0.00380;1.39951;3.02123;,
 0.00380;2.42896;2.09473;,
 0.00380;2.80576;0.00234;,
 0.00380;2.42896;-1.26328;,
 0.00380;1.39951;-2.18978;,
 0.00380;-0.00674;-2.52891;,
 -0.72412;-1.36507;-2.11510;,
 -0.72412;-0.00674;-2.44266;,
 -0.72412;-2.35944;-1.22016;,
 -0.72412;-2.72340;0.00234;,
 -1.08808;-2.35944;2.05160;,
 -1.08808;-1.36507;2.94654;,
 -1.08808;-0.00674;3.27410;,
 -1.08808;1.35160;2.94654;,
 -1.08808;2.34597;2.05160;,
 -0.72412;2.70993;0.00234;,
 -0.72412;2.34597;-1.22016;,
 -0.72412;1.35160;-2.11510;,
 -0.72412;-0.00674;-2.44266;,
 -1.40245;-1.22459;-1.89610;,
 -1.40245;-0.00674;-2.18979;,
 -1.40245;-2.11611;-1.09373;,
 -1.40245;-2.44244;0.00234;,
 -2.10557;-2.11611;1.92517;,
 -2.10557;-1.22459;2.72754;,
 -2.10557;-0.00674;3.02123;,
 -2.10557;1.21111;2.72754;,
 -2.10557;2.10264;1.92517;,
 -1.40245;2.42896;0.00234;,
 -1.40245;2.10264;-1.09373;,
 -1.40245;1.21111;-1.89610;,
 -1.40245;-0.00674;-2.18979;,
 -1.98494;-1.00111;-1.54773;,
 -1.98494;-0.00674;-1.78752;,
 -1.98494;-1.72904;-0.89260;,
 -1.98494;-1.99547;0.00234;,
 -2.97930;-1.72904;1.72404;,
 -2.97930;-1.00111;2.37917;,
 -2.97930;-0.00674;2.61896;,
 -2.97930;0.98763;2.37917;,
 -2.97930;1.71556;1.72404;,
 -1.98494;1.98200;0.00234;,
 -1.98494;1.71556;-0.89259;,
 -1.98494;0.98763;-1.54773;,
 -1.98494;-0.00674;-1.78752;,
 -2.43190;-0.70986;-1.09373;,
 -2.43190;-0.00674;-1.26328;,
 -2.43190;-1.22459;-0.63047;,
 -2.43190;-1.41299;0.00234;,
 -3.64975;-1.22459;1.46191;,
 -3.64975;-0.70986;1.92517;,
 -3.64975;-0.00674;2.09473;,
 -3.64975;0.69639;1.92517;,
 -3.64975;1.21111;1.46191;,
 -2.43190;1.39951;0.00234;,
 -2.43190;1.21111;-0.63047;,
 -2.43190;0.69639;-1.09373;,
 -2.43190;-0.00674;-1.26328;,
 -2.71287;-0.37070;-0.56503;,
 -2.71287;-0.00674;-0.65279;,
 -2.71287;-0.63714;-0.32523;,
 -2.71287;-0.73466;0.00234;,
 -2.71287;-0.63714;0.32991;,
 -4.07120;-0.37070;1.39647;,
 -4.07120;-0.00674;1.48423;,
 -4.07120;0.35722;1.39647;,
 -2.71287;0.62367;0.32991;,
 -2.71287;0.72119;0.00234;,
 -2.71287;0.62367;-0.32523;,
 -2.71287;0.35723;-0.56503;,
 -2.71287;-0.00674;-0.65279;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;,
 -2.80870;-0.00674;0.00234;;
 
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
  138;
  0.959819;0.000000;-0.280619;,
  0.958821;-0.000000;-0.284011;,
  0.960602;-0.128332;-0.246525;,
  0.964203;-0.223312;-0.142987;,
  0.970818;-0.216817;-0.102480;,
  0.901066;-0.324875;-0.287291;,
  0.805603;-0.262580;-0.531089;,
  0.761207;0.000000;-0.648509;,
  0.805603;0.262581;-0.531089;,
  0.901066;0.324876;-0.287291;,
  0.970818;0.216817;-0.102479;,
  0.964203;0.223312;-0.142986;,
  0.960602;0.128332;-0.246525;,
  0.842882;0.000000;-0.538099;,
  0.848582;-0.244786;-0.469029;,
  0.860311;-0.429642;-0.274360;,
  0.839984;-0.489075;-0.235015;,
  0.849562;-0.524293;-0.057967;,
  0.802098;-0.355064;0.480176;,
  0.728234;0.000000;0.685328;,
  0.802097;0.355065;0.480176;,
  0.849562;0.524294;-0.057966;,
  0.839984;0.489076;-0.235014;,
  0.860311;0.429643;-0.274359;,
  0.848582;0.244787;-0.469029;,
  0.670638;0.000000;-0.741785;,
  0.679409;-0.340356;-0.650047;,
  0.697885;-0.604246;-0.384505;,
  0.634489;-0.744256;-0.208583;,
  0.610368;-0.756181;0.235882;,
  0.530047;-0.394016;0.750867;,
  0.520878;0.000000;0.853631;,
  0.530047;0.394017;0.750867;,
  0.610369;0.756181;0.235882;,
  0.634491;0.744255;-0.208583;,
  0.697885;0.604245;-0.384505;,
  0.679409;0.340357;-0.650047;,
  0.462630;0.000000;-0.886552;,
  0.471410;-0.410021;-0.780804;,
  0.490329;-0.735996;-0.466784;,
  0.451629;-0.883286;-0.125840;,
  0.402879;-0.832917;0.379390;,
  0.338550;-0.437929;0.832828;,
  0.331301;-0.000000;0.943525;,
  0.338551;0.437929;0.832827;,
  0.402881;0.832917;0.379390;,
  0.451632;0.883285;-0.125841;,
  0.490331;0.735994;-0.466784;,
  0.471412;0.410021;-0.780803;,
  0.235333;0.000000;-0.971915;,
  0.240761;-0.451948;-0.858939;,
  0.252643;-0.817631;-0.517350;,
  0.234264;-0.969226;-0.075639;,
  0.198074;-0.866326;0.458526;,
  0.164447;-0.459470;0.872837;,
  0.160570;-0.000001;0.987025;,
  0.164448;0.459470;0.872837;,
  0.198074;0.866326;0.458526;,
  0.234263;0.969226;-0.075640;,
  0.252642;0.817631;-0.517351;,
  0.240760;0.451948;-0.858940;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.465899;-0.884838;,
  -0.000000;-0.845245;-0.534379;,
  -0.000000;-0.998231;-0.059451;,
  -0.000000;-0.875507;0.483205;,
  0.000000;-0.465935;0.884819;,
  0.000000;-0.000001;1.000000;,
  0.000000;0.465934;0.884819;,
  -0.000000;0.875507;0.483205;,
  -0.000000;0.998231;-0.059450;,
  -0.000000;0.845245;-0.534379;,
  -0.000000;0.465898;-0.884839;,
  -0.235333;0.000000;-0.971915;,
  -0.240761;-0.451948;-0.858939;,
  -0.252643;-0.817631;-0.517350;,
  -0.234264;-0.969226;-0.075640;,
  -0.198074;-0.866326;0.458526;,
  -0.164447;-0.459470;0.872837;,
  -0.160570;-0.000001;0.987025;,
  -0.164448;0.459470;0.872837;,
  -0.198074;0.866326;0.458526;,
  -0.234263;0.969226;-0.075640;,
  -0.252643;0.817631;-0.517351;,
  -0.240761;0.451948;-0.858940;,
  -0.462628;-0.000000;-0.886553;,
  -0.471408;-0.410022;-0.780805;,
  -0.490327;-0.735997;-0.466785;,
  -0.451627;-0.883287;-0.125840;,
  -0.402878;-0.832918;0.379390;,
  -0.338550;-0.437929;0.832828;,
  -0.331301;-0.000000;0.943525;,
  -0.338550;0.437929;0.832828;,
  -0.402880;0.832917;0.379390;,
  -0.451629;0.883286;-0.125841;,
  -0.490329;0.735996;-0.466785;,
  -0.471410;0.410022;-0.780804;,
  -0.670635;0.000000;-0.741788;,
  -0.679406;-0.340357;-0.650050;,
  -0.697882;-0.604248;-0.384506;,
  -0.634487;-0.744258;-0.208582;,
  -0.610366;-0.756183;0.235883;,
  -0.530044;-0.394017;0.750869;,
  -0.520876;0.000000;0.853632;,
  -0.530044;0.394017;0.750869;,
  -0.610366;0.756182;0.235883;,
  -0.634488;0.744257;-0.208583;,
  -0.697882;0.604248;-0.384506;,
  -0.679407;0.340358;-0.650049;,
  -0.842882;-0.000000;-0.538099;,
  -0.848583;-0.244786;-0.469028;,
  -0.860311;-0.429641;-0.274359;,
  -0.839984;-0.489075;-0.235015;,
  -0.849563;-0.524293;-0.057967;,
  -0.802098;-0.355064;0.480176;,
  -0.728235;0.000000;0.685328;,
  -0.802098;0.355064;0.480176;,
  -0.849563;0.524293;-0.057967;,
  -0.839984;0.489075;-0.235015;,
  -0.860311;0.429643;-0.274359;,
  -0.848582;0.244787;-0.469028;,
  -0.958823;-0.000000;-0.284005;,
  -0.960604;-0.128329;-0.246520;,
  -0.964204;-0.223307;-0.142983;,
  -0.970820;-0.216811;-0.102480;,
  -0.901067;-0.324869;-0.287294;,
  -0.924675;-0.262004;-0.276280;,
  -0.822947;-0.000000;0.568118;,
  -0.924675;0.262004;-0.276280;,
  -0.901067;0.324870;-0.287293;,
  -0.970820;0.216811;-0.102479;,
  -0.964204;0.223308;-0.142982;,
  -0.960604;0.128330;-0.246519;,
  -0.959820;0.000000;-0.280617;,
  0.815329;-0.135732;0.562864;,
  0.822944;0.000000;0.568123;,
  0.815328;0.135732;0.562866;,
  -0.761206;0.000000;-0.648511;;
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
  4;1,2,14,13;,
  4;2,3,15,14;,
  4;3,4,16,15;,
  4;4,5,17,16;,
  4;5,6,18,17;,
  4;134,135,19,18;,
  4;135,136,20,19;,
  4;8,9,21,20;,
  4;9,10,22,21;,
  4;10,11,23,22;,
  4;11,12,24,23;,
  4;12,1,13,24;,
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
  4;99,100,112,111;,
  4;100,101,113,112;,
  4;101,102,114,113;,
  4;102,103,115,114;,
  4;103,104,116,115;,
  4;104,105,117,116;,
  4;105,106,118,117;,
  4;106,107,119,118;,
  4;107,108,120,119;,
  4;108,97,109,120;,
  4;109,110,122,121;,
  4;110,111,123,122;,
  4;111,112,124,123;,
  4;112,113,125,124;,
  4;113,114,126,125;,
  4;114,115,127,126;,
  4;115,116,128,127;,
  4;116,117,129,128;,
  4;117,118,130,129;,
  4;118,119,131,130;,
  4;119,120,132,131;,
  4;120,109,121,132;,
  3;121,122,133;,
  3;122,123,133;,
  3;123,124,133;,
  3;124,125,133;,
  3;125,126,133;,
  3;126,137,133;,
  3;137,128,133;,
  3;128,129,133;,
  3;129,130,133;,
  3;130,131,133;,
  3;131,132,133;,
  3;132,121,133;;
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
