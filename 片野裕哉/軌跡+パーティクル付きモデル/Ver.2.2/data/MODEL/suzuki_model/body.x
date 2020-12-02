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
 173;
 0.00000;23.75570;-2.00000;,
 0.51764;23.75570;-1.93185;,
 1.07219;16.78226;-4.00146;,
 0.00000;16.78226;-4.14262;,
 1.00000;23.75570;-1.73205;,
 2.07131;16.78226;-3.58761;,
 1.41421;23.75570;-1.41421;,
 2.92927;16.78226;-2.92927;,
 1.73205;23.75570;-1.00000;,
 3.58761;16.78226;-2.07131;,
 1.93185;23.75570;-0.51764;,
 4.00146;16.78226;-1.07219;,
 2.00000;23.75570;-0.00000;,
 4.14262;16.78226;-0.00000;,
 1.93185;23.75570;0.51764;,
 4.00146;16.78226;1.07219;,
 1.73205;23.75570;1.00000;,
 3.58761;16.78226;2.07131;,
 1.41421;23.75570;1.41421;,
 2.92927;16.78226;2.92927;,
 1.00000;23.75570;1.73205;,
 2.07131;16.78226;3.58761;,
 0.51764;23.75570;1.93185;,
 1.07219;16.78226;4.00146;,
 0.00000;23.75570;2.00000;,
 0.00000;16.78226;4.14262;,
 -0.51764;23.75570;1.93185;,
 -1.07219;16.78226;4.00146;,
 -1.00000;23.75570;1.73205;,
 -2.07131;16.78226;3.58761;,
 -1.41421;23.75570;1.41421;,
 -2.92927;16.78226;2.92928;,
 -1.73205;23.75570;1.00000;,
 -3.58761;16.78226;2.07131;,
 -1.93185;23.75570;0.51764;,
 -4.00146;16.78226;1.07219;,
 -2.00000;23.75570;0.00000;,
 -4.14262;16.78226;0.00000;,
 -1.93185;23.75570;-0.51764;,
 -4.00146;16.78226;-1.07219;,
 -1.73205;23.75570;-1.00000;,
 -3.58761;16.78226;-2.07131;,
 -1.41421;23.75570;-1.41421;,
 -2.92928;16.78226;-2.92927;,
 -1.00000;23.75570;-1.73205;,
 -2.07131;16.78226;-3.58761;,
 -0.51764;23.75570;-1.93185;,
 -1.07219;16.78226;-4.00146;,
 0.00000;23.75570;-2.00000;,
 0.00000;16.78226;-4.14262;,
 1.07219;11.60400;-4.00146;,
 0.00000;11.60400;-4.14262;,
 2.07131;11.60400;-3.58761;,
 2.92927;11.60400;-2.92927;,
 3.58761;11.60400;-2.07131;,
 4.00146;11.60400;-1.07219;,
 4.14262;11.60400;-0.00000;,
 4.00146;11.60400;1.07219;,
 3.58761;11.60400;2.07131;,
 2.92927;11.60400;2.92927;,
 2.07131;11.60400;3.58761;,
 1.07219;11.60400;4.00146;,
 0.00000;11.60400;4.14262;,
 -1.07219;11.60400;4.00146;,
 -2.07131;11.60400;3.58761;,
 -2.92927;11.60400;2.92928;,
 -3.58761;11.60400;2.07131;,
 -4.00146;11.60400;1.07219;,
 -4.14262;11.60400;0.00000;,
 -4.00146;11.60400;-1.07219;,
 -3.58761;11.60400;-2.07131;,
 -2.92928;11.60400;-2.92927;,
 -2.07131;11.60400;-3.58761;,
 -1.07219;11.60400;-4.00146;,
 0.00000;11.60400;-4.14262;,
 1.27033;5.65446;-4.74094;,
 0.00000;5.65446;-4.90819;,
 2.45409;5.65446;-4.25061;,
 3.47061;5.65446;-3.47061;,
 4.25061;5.65446;-2.45409;,
 4.74094;5.65446;-1.27033;,
 4.90819;5.65446;-0.00000;,
 4.74094;5.65446;1.27033;,
 4.25061;5.65446;2.45409;,
 3.47061;5.65446;3.47061;,
 2.45409;5.65446;4.25061;,
 1.27033;5.65446;4.74094;,
 0.00000;5.65446;4.90819;,
 -1.27033;5.65446;4.74094;,
 -2.45409;5.65446;4.25061;,
 -3.47061;5.65446;3.47061;,
 -4.25061;5.65446;2.45409;,
 -4.74094;5.65446;1.27033;,
 -4.90819;5.65446;0.00000;,
 -4.74094;5.65446;-1.27033;,
 -4.25061;5.65446;-2.45409;,
 -3.47061;5.65446;-3.47061;,
 -2.45410;5.65446;-4.25061;,
 -1.27034;5.65446;-4.74094;,
 0.00000;5.65446;-4.90819;,
 1.27033;0.21847;-4.74094;,
 0.00000;0.21847;-4.90819;,
 2.45409;0.21847;-4.25061;,
 3.47061;0.21847;-3.47061;,
 4.25061;0.21847;-2.45409;,
 4.74094;0.21847;-1.27033;,
 4.90819;0.21847;-0.00000;,
 4.74094;0.21847;1.27033;,
 4.25061;0.21847;2.45409;,
 3.47061;0.21847;3.47061;,
 2.45409;0.21847;4.25061;,
 1.27033;0.21847;4.74094;,
 0.00000;0.21847;4.90819;,
 -1.27033;0.21847;4.74094;,
 -2.45409;0.21847;4.25061;,
 -3.47061;0.21847;3.47061;,
 -4.25061;0.21847;2.45409;,
 -4.74094;0.21847;1.27033;,
 -4.90819;0.21847;0.00000;,
 -4.74094;0.21847;-1.27033;,
 -4.25061;0.21847;-2.45409;,
 -3.47061;0.21847;-3.47061;,
 -2.45410;0.21847;-4.25061;,
 -1.27034;0.21847;-4.74094;,
 0.00000;0.21847;-4.90819;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;23.75570;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;,
 0.00000;0.21847;0.00000;;
 
 144;
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
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;3,2,50,51;,
 4;2,5,52,50;,
 4;5,7,53,52;,
 4;7,9,54,53;,
 4;9,11,55,54;,
 4;11,13,56,55;,
 4;13,15,57,56;,
 4;15,17,58,57;,
 4;17,19,59,58;,
 4;19,21,60,59;,
 4;21,23,61,60;,
 4;23,25,62,61;,
 4;25,27,63,62;,
 4;27,29,64,63;,
 4;29,31,65,64;,
 4;31,33,66,65;,
 4;33,35,67,66;,
 4;35,37,68,67;,
 4;37,39,69,68;,
 4;39,41,70,69;,
 4;41,43,71,70;,
 4;43,45,72,71;,
 4;45,47,73,72;,
 4;47,49,74,73;,
 4;51,50,75,76;,
 4;50,52,77,75;,
 4;52,53,78,77;,
 4;53,54,79,78;,
 4;54,55,80,79;,
 4;55,56,81,80;,
 4;56,57,82,81;,
 4;57,58,83,82;,
 4;58,59,84,83;,
 4;59,60,85,84;,
 4;60,61,86,85;,
 4;61,62,87,86;,
 4;62,63,88,87;,
 4;63,64,89,88;,
 4;64,65,90,89;,
 4;65,66,91,90;,
 4;66,67,92,91;,
 4;67,68,93,92;,
 4;68,69,94,93;,
 4;69,70,95,94;,
 4;70,71,96,95;,
 4;71,72,97,96;,
 4;72,73,98,97;,
 4;73,74,99,98;,
 4;76,75,100,101;,
 4;75,77,102,100;,
 4;77,78,103,102;,
 4;78,79,104,103;,
 4;79,80,105,104;,
 4;80,81,106,105;,
 4;81,82,107,106;,
 4;82,83,108,107;,
 4;83,84,109,108;,
 4;84,85,110,109;,
 4;85,86,111,110;,
 4;86,87,112,111;,
 4;87,88,113,112;,
 4;88,89,114,113;,
 4;89,90,115,114;,
 4;90,91,116,115;,
 4;91,92,117,116;,
 4;92,93,118,117;,
 4;93,94,119,118;,
 4;94,95,120,119;,
 4;95,96,121,120;,
 4;96,97,122,121;,
 4;97,98,123,122;,
 4;98,99,124,123;,
 3;125,1,0;,
 3;126,4,1;,
 3;127,6,4;,
 3;128,8,6;,
 3;129,10,8;,
 3;130,12,10;,
 3;131,14,12;,
 3;132,16,14;,
 3;133,18,16;,
 3;134,20,18;,
 3;135,22,20;,
 3;136,24,22;,
 3;137,26,24;,
 3;138,28,26;,
 3;139,30,28;,
 3;140,32,30;,
 3;141,34,32;,
 3;142,36,34;,
 3;143,38,36;,
 3;144,40,38;,
 3;145,42,40;,
 3;146,44,42;,
 3;147,46,44;,
 3;148,48,46;,
 3;149,101,100;,
 3;150,100,102;,
 3;151,102,103;,
 3;152,103,104;,
 3;153,104,105;,
 3;154,105,106;,
 3;155,106,107;,
 3;156,107,108;,
 3;157,108,109;,
 3;158,109,110;,
 3;159,110,111;,
 3;160,111,112;,
 3;161,112,113;,
 3;162,113,114;,
 3;163,114,115;,
 3;164,115,116;,
 3;165,116,117;,
 3;166,117,118;,
 3;167,118,119;,
 3;168,119,120;,
 3;169,120,121;,
 3;170,121,122;,
 3;171,122,123;,
 3;172,123,124;;
 
 MeshMaterialList {
  1;
  144;
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
   0.263529;0.263529;0.263529;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  121;
  0.000000;1.000000;0.000000;,
  -0.000000;0.293703;-0.955897;,
  0.247405;0.293703;-0.923325;,
  0.477948;0.293703;-0.827831;,
  0.675921;0.293703;-0.675921;,
  0.827831;0.293703;-0.477948;,
  0.923325;0.293703;-0.247404;,
  0.955897;0.293703;-0.000000;,
  0.923325;0.293703;0.247404;,
  0.827831;0.293703;0.477948;,
  0.675921;0.293703;0.675921;,
  0.477948;0.293703;0.827831;,
  0.247405;0.293703;0.923325;,
  0.000001;0.293703;0.955897;,
  -0.247404;0.293703;0.923325;,
  -0.477948;0.293703;0.827831;,
  -0.675921;0.293703;0.675921;,
  -0.827831;0.293703;0.477948;,
  -0.923325;0.293703;0.247405;,
  -0.955897;0.293703;0.000001;,
  -0.923325;0.293703;-0.247404;,
  -0.827831;0.293703;-0.477948;,
  -0.675921;0.293703;-0.675921;,
  -0.477949;0.293703;-0.827831;,
  -0.247405;0.293703;-0.923325;,
  -0.000000;0.148552;-0.988905;,
  0.255948;0.148552;-0.955208;,
  0.494451;0.148552;-0.856417;,
  0.699261;0.148553;-0.699261;,
  0.856417;0.148552;-0.494451;,
  0.955208;0.148552;-0.255947;,
  0.988905;0.148552;-0.000000;,
  0.955208;0.148552;0.255947;,
  0.856417;0.148552;0.494452;,
  0.699261;0.148553;0.699261;,
  0.494452;0.148552;0.856417;,
  0.255948;0.148552;0.955208;,
  0.000002;0.148552;0.988905;,
  -0.255947;0.148553;0.955208;,
  -0.494452;0.148552;0.856416;,
  -0.699261;0.148553;0.699261;,
  -0.856417;0.148552;0.494452;,
  -0.955208;0.148552;0.255948;,
  -0.988905;0.148552;0.000002;,
  -0.955209;0.148553;-0.255947;,
  -0.856416;0.148553;-0.494452;,
  -0.699261;0.148553;-0.699261;,
  -0.494452;0.148552;-0.856416;,
  -0.255948;0.148552;-0.955208;,
  0.000000;0.063948;-0.997953;,
  0.258290;0.063948;-0.963949;,
  0.498975;0.063948;-0.864254;,
  0.705659;0.063948;-0.705660;,
  0.864254;0.063948;-0.498975;,
  0.963949;0.063948;-0.258290;,
  0.997953;0.063948;-0.000000;,
  0.963949;0.063948;0.258290;,
  0.864253;0.063948;0.498976;,
  0.705660;0.063948;0.705659;,
  0.498976;0.063948;0.864253;,
  0.258290;0.063948;0.963949;,
  0.000002;0.063948;0.997953;,
  -0.258289;0.063948;0.963949;,
  -0.498976;0.063948;0.864253;,
  -0.705659;0.063948;0.705660;,
  -0.864253;0.063948;0.498976;,
  -0.963949;0.063948;0.258290;,
  -0.997953;0.063948;0.000002;,
  -0.963949;0.063948;-0.258289;,
  -0.864253;0.063948;-0.498976;,
  -0.705660;0.063948;-0.705659;,
  -0.498977;0.063948;-0.864253;,
  -0.258290;0.063948;-0.963949;,
  0.000000;0.063948;-0.997953;,
  0.258290;0.063948;-0.963949;,
  0.498976;0.063948;-0.864253;,
  0.705659;0.063948;-0.705660;,
  0.864253;0.063948;-0.498976;,
  0.963949;0.063948;-0.258290;,
  0.997953;0.063948;-0.000000;,
  0.963949;0.063948;0.258290;,
  0.864253;0.063948;0.498976;,
  0.705660;0.063948;0.705659;,
  0.498976;0.063948;0.864253;,
  0.258290;0.063948;0.963949;,
  0.000001;0.063948;0.997953;,
  -0.258289;0.063948;0.963949;,
  -0.498976;0.063948;0.864253;,
  -0.864253;0.063948;0.498976;,
  -0.963948;0.063948;0.258290;,
  -0.997953;0.063948;0.000001;,
  -0.963949;0.063948;-0.258289;,
  -0.864253;0.063948;-0.498976;,
  -0.705660;0.063948;-0.705659;,
  -0.498976;0.063948;-0.864253;,
  -0.258290;0.063948;-0.963949;,
  0.000000;0.000000;-1.000000;,
  0.258820;0.000000;-0.965926;,
  0.499999;0.000000;-0.866026;,
  0.707107;0.000000;-0.707107;,
  0.866026;0.000000;-0.499999;,
  0.965926;0.000000;-0.258820;,
  1.000000;0.000000;0.000000;,
  0.965926;0.000000;0.258820;,
  0.866026;0.000000;0.499999;,
  0.707107;0.000000;0.707107;,
  0.499999;0.000000;0.866026;,
  0.258820;0.000000;0.965926;,
  0.000000;0.000000;1.000000;,
  -0.258819;0.000000;0.965926;,
  -0.499999;0.000000;0.866026;,
  -0.707107;0.000000;0.707107;,
  -0.866026;0.000000;0.499999;,
  -0.965926;0.000000;0.258820;,
  -1.000000;0.000000;0.000000;,
  -0.965926;0.000000;-0.258819;,
  -0.866026;0.000000;-0.499999;,
  -0.707107;0.000000;-0.707107;,
  -0.500000;0.000000;-0.866026;,
  -0.258820;0.000000;-0.965926;,
  0.000000;-1.000000;-0.000000;;
  144;
  4;1,2,26,25;,
  4;2,3,27,26;,
  4;3,4,28,27;,
  4;4,5,29,28;,
  4;5,6,30,29;,
  4;6,7,31,30;,
  4;7,8,32,31;,
  4;8,9,33,32;,
  4;9,10,34,33;,
  4;10,11,35,34;,
  4;11,12,36,35;,
  4;12,13,37,36;,
  4;13,14,38,37;,
  4;14,15,39,38;,
  4;15,16,40,39;,
  4;16,17,41,40;,
  4;17,18,42,41;,
  4;18,19,43,42;,
  4;19,20,44,43;,
  4;20,21,45,44;,
  4;21,22,46,45;,
  4;22,23,47,46;,
  4;23,24,48,47;,
  4;24,1,25,48;,
  4;25,26,50,49;,
  4;26,27,51,50;,
  4;27,28,52,51;,
  4;28,29,53,52;,
  4;29,30,54,53;,
  4;30,31,55,54;,
  4;31,32,56,55;,
  4;32,33,57,56;,
  4;33,34,58,57;,
  4;34,35,59,58;,
  4;35,36,60,59;,
  4;36,37,61,60;,
  4;37,38,62,61;,
  4;38,39,63,62;,
  4;39,40,64,63;,
  4;40,41,65,64;,
  4;41,42,66,65;,
  4;42,43,67,66;,
  4;43,44,68,67;,
  4;44,45,69,68;,
  4;45,46,70,69;,
  4;46,47,71,70;,
  4;47,48,72,71;,
  4;48,25,49,72;,
  4;49,50,74,73;,
  4;50,51,75,74;,
  4;51,52,76,75;,
  4;52,53,77,76;,
  4;53,54,78,77;,
  4;54,55,79,78;,
  4;55,56,80,79;,
  4;56,57,81,80;,
  4;57,58,82,81;,
  4;58,59,83,82;,
  4;59,60,84,83;,
  4;60,61,85,84;,
  4;61,62,86,85;,
  4;62,63,87,86;,
  4;63,64,64,87;,
  4;64,65,88,64;,
  4;65,66,89,88;,
  4;66,67,90,89;,
  4;67,68,91,90;,
  4;68,69,92,91;,
  4;69,70,93,92;,
  4;70,71,94,93;,
  4;71,72,95,94;,
  4;72,49,73,95;,
  4;73,74,97,96;,
  4;74,75,98,97;,
  4;75,76,99,98;,
  4;76,77,100,99;,
  4;77,78,101,100;,
  4;78,79,102,101;,
  4;79,80,103,102;,
  4;80,81,104,103;,
  4;81,82,105,104;,
  4;82,83,106,105;,
  4;83,84,107,106;,
  4;84,85,108,107;,
  4;85,86,109,108;,
  4;86,87,110,109;,
  4;87,64,111,110;,
  4;64,88,112,111;,
  4;88,89,113,112;,
  4;89,90,114,113;,
  4;90,91,115,114;,
  4;91,92,116,115;,
  4;92,93,117,116;,
  4;93,94,118,117;,
  4;94,95,119,118;,
  4;95,73,96,119;,
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
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;,
  3;120,120,120;;
 }
 MeshTextureCoords {
  173;
  0.000000;0.000000;,
  0.041667;0.000000;,
  0.041667;0.250000;,
  0.000000;0.250000;,
  0.083333;0.000000;,
  0.083333;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.166667;0.000000;,
  0.166667;0.250000;,
  0.208333;0.000000;,
  0.208333;0.250000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.291667;0.000000;,
  0.291667;0.250000;,
  0.333333;0.000000;,
  0.333333;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.416667;0.000000;,
  0.416667;0.250000;,
  0.458333;0.000000;,
  0.458333;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.541667;0.000000;,
  0.541667;0.250000;,
  0.583333;0.000000;,
  0.583333;0.250000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.666667;0.000000;,
  0.666667;0.250000;,
  0.708333;0.000000;,
  0.708333;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.791667;0.000000;,
  0.791667;0.250000;,
  0.833333;0.000000;,
  0.833333;0.250000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.916667;0.000000;,
  0.916667;0.250000;,
  0.958333;0.000000;,
  0.958333;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.041667;0.500000;,
  0.000000;0.500000;,
  0.083333;0.500000;,
  0.125000;0.500000;,
  0.166667;0.500000;,
  0.208333;0.500000;,
  0.250000;0.500000;,
  0.291667;0.500000;,
  0.333333;0.500000;,
  0.375000;0.500000;,
  0.416667;0.500000;,
  0.458333;0.500000;,
  0.500000;0.500000;,
  0.541667;0.500000;,
  0.583333;0.500000;,
  0.625000;0.500000;,
  0.666667;0.500000;,
  0.708333;0.500000;,
  0.750000;0.500000;,
  0.791667;0.500000;,
  0.833333;0.500000;,
  0.875000;0.500000;,
  0.916667;0.500000;,
  0.958333;0.500000;,
  1.000000;0.500000;,
  0.041667;0.750000;,
  0.000000;0.750000;,
  0.083333;0.750000;,
  0.125000;0.750000;,
  0.166667;0.750000;,
  0.208333;0.750000;,
  0.250000;0.750000;,
  0.291667;0.750000;,
  0.333333;0.750000;,
  0.375000;0.750000;,
  0.416667;0.750000;,
  0.458333;0.750000;,
  0.500000;0.750000;,
  0.541667;0.750000;,
  0.583333;0.750000;,
  0.625000;0.750000;,
  0.666667;0.750000;,
  0.708333;0.750000;,
  0.750000;0.750000;,
  0.791667;0.750000;,
  0.833333;0.750000;,
  0.875000;0.750000;,
  0.916667;0.750000;,
  0.958333;0.750000;,
  1.000000;0.750000;,
  0.041667;1.000000;,
  0.000000;1.000000;,
  0.083333;1.000000;,
  0.125000;1.000000;,
  0.166667;1.000000;,
  0.208333;1.000000;,
  0.250000;1.000000;,
  0.291667;1.000000;,
  0.333333;1.000000;,
  0.375000;1.000000;,
  0.416667;1.000000;,
  0.458333;1.000000;,
  0.500000;1.000000;,
  0.541667;1.000000;,
  0.583333;1.000000;,
  0.625000;1.000000;,
  0.666667;1.000000;,
  0.708333;1.000000;,
  0.750000;1.000000;,
  0.791667;1.000000;,
  0.833333;1.000000;,
  0.875000;1.000000;,
  0.916667;1.000000;,
  0.958333;1.000000;,
  1.000000;1.000000;,
  0.020833;0.000000;,
  0.062500;0.000000;,
  0.104167;0.000000;,
  0.145833;0.000000;,
  0.187500;0.000000;,
  0.229167;0.000000;,
  0.270833;0.000000;,
  0.312500;0.000000;,
  0.354167;0.000000;,
  0.395833;0.000000;,
  0.437500;0.000000;,
  0.479167;0.000000;,
  0.520833;0.000000;,
  0.562500;0.000000;,
  0.604167;0.000000;,
  0.645833;0.000000;,
  0.687500;0.000000;,
  0.729167;0.000000;,
  0.770833;0.000000;,
  0.812500;0.000000;,
  0.854167;0.000000;,
  0.895833;0.000000;,
  0.937500;0.000000;,
  0.979167;0.000000;,
  0.020833;1.000000;,
  0.062500;1.000000;,
  0.104167;1.000000;,
  0.145833;1.000000;,
  0.187500;1.000000;,
  0.229167;1.000000;,
  0.270833;1.000000;,
  0.312500;1.000000;,
  0.354167;1.000000;,
  0.395833;1.000000;,
  0.437500;1.000000;,
  0.479167;1.000000;,
  0.520833;1.000000;,
  0.562500;1.000000;,
  0.604167;1.000000;,
  0.645833;1.000000;,
  0.687500;1.000000;,
  0.729167;1.000000;,
  0.770833;1.000000;,
  0.812500;1.000000;,
  0.854167;1.000000;,
  0.895833;1.000000;,
  0.937500;1.000000;,
  0.979167;1.000000;;
 }
}
