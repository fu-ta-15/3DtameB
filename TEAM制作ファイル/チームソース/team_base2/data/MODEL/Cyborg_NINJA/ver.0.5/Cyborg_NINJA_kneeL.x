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
 180;
 0.00000;3.75000;0.00000;,
 0.64705;3.62222;-1.12072;,
 0.00000;3.62222;-1.29410;,
 0.00000;3.75000;0.00000;,
 1.12072;3.62222;-0.64705;,
 0.00000;3.75000;0.00000;,
 1.29409;3.62222;0.00000;,
 0.00000;3.75000;0.00000;,
 1.12072;3.62222;0.64705;,
 0.00000;3.75000;0.00000;,
 0.64705;3.62222;1.12072;,
 0.00000;3.75000;0.00000;,
 0.00000;3.62222;1.29410;,
 0.00000;3.75000;0.00000;,
 -0.64705;3.62222;1.12072;,
 0.00000;3.75000;0.00000;,
 -1.12072;3.62222;0.64705;,
 0.00000;3.75000;0.00000;,
 -1.29409;3.62222;0.00000;,
 0.00000;3.75000;0.00000;,
 -1.12072;3.62222;-0.64705;,
 0.00000;3.75000;0.00000;,
 -0.64705;3.62222;-1.12072;,
 0.00000;3.75000;0.00000;,
 0.00000;3.62222;-1.29410;,
 1.25000;3.24760;-2.16506;,
 0.00000;3.24760;-2.50000;,
 2.16506;3.24760;-1.25000;,
 2.50000;3.24760;0.00000;,
 2.16506;3.24760;1.25000;,
 1.25000;3.24760;2.16506;,
 0.00000;3.24760;2.50000;,
 -1.25000;3.24760;2.16506;,
 -2.16506;3.24760;1.25000;,
 -2.50000;3.24760;0.00000;,
 -2.16506;3.24760;-1.25000;,
 -1.25000;3.24760;-2.16506;,
 0.00000;3.24760;-2.50000;,
 1.76777;2.65165;-3.06186;,
 0.00000;2.65165;-3.53553;,
 3.06186;2.65165;-1.76777;,
 3.53553;2.65165;0.00000;,
 3.06186;2.65165;1.76777;,
 1.76777;2.65165;3.06186;,
 0.00000;2.65165;3.53553;,
 -1.76777;2.65165;3.06186;,
 -3.06186;2.65165;1.76777;,
 -3.53553;2.65165;0.00000;,
 -3.06186;2.65165;-1.76777;,
 -1.76777;2.65165;-3.06186;,
 0.00000;2.65165;-3.53553;,
 2.16506;1.87500;-3.75000;,
 0.00000;1.87500;-4.33013;,
 3.75000;1.87500;-2.16506;,
 4.33013;1.87500;0.00000;,
 3.75000;1.87500;2.16506;,
 2.16506;1.87500;3.75000;,
 0.00000;1.87500;4.33013;,
 -2.16506;1.87500;3.75000;,
 -3.75000;1.87500;2.16507;,
 -4.33013;1.87500;0.00000;,
 -3.75000;1.87500;-2.16506;,
 -2.16507;1.87500;-3.75000;,
 0.00000;1.87500;-4.33013;,
 2.41481;0.97057;-4.18258;,
 0.00000;0.97057;-4.82963;,
 4.18258;0.97057;-2.41481;,
 4.82963;0.97057;0.00000;,
 4.18258;0.97057;2.41481;,
 2.41481;0.97057;4.18258;,
 0.00000;0.97057;4.82963;,
 -2.41481;0.97057;4.18258;,
 -4.18258;0.97057;2.41482;,
 -4.82963;0.97057;0.00000;,
 -4.18258;0.97057;-2.41481;,
 -2.41482;0.97057;-4.18258;,
 0.00000;0.97057;-4.82963;,
 2.50000;0.00000;-4.33013;,
 0.00000;0.00000;-5.00000;,
 4.33013;0.00000;-2.50000;,
 5.00000;0.00000;0.00000;,
 4.33013;0.00000;2.50000;,
 2.50000;0.00000;4.33013;,
 0.00000;0.00000;5.00000;,
 -2.50000;0.00000;4.33013;,
 -4.33013;0.00000;2.50000;,
 -5.00000;0.00000;0.00000;,
 -4.33013;0.00000;-2.50000;,
 -2.50000;0.00000;-4.33013;,
 0.00000;0.00000;-5.00000;,
 2.41481;-0.97057;-4.18258;,
 0.00000;-0.97057;-4.82963;,
 4.18258;-0.97057;-2.41481;,
 4.82963;-0.97057;0.00000;,
 4.18258;-0.97057;2.41481;,
 2.41481;-0.97057;4.18258;,
 0.00000;-0.97057;4.82963;,
 -2.41481;-0.97057;4.18258;,
 -4.18258;-0.97057;2.41482;,
 -4.82963;-0.97057;0.00000;,
 -4.18258;-0.97057;-2.41481;,
 -2.41482;-0.97057;-4.18258;,
 0.00000;-0.97057;-4.82963;,
 2.16506;-1.87500;-3.75000;,
 0.00000;-1.87500;-4.33013;,
 3.75000;-1.87500;-2.16506;,
 4.33013;-1.87500;0.00000;,
 3.75000;-1.87500;2.16506;,
 2.16506;-1.87500;3.75000;,
 0.00000;-1.87500;4.33013;,
 -2.16506;-1.87500;3.75000;,
 -3.75000;-1.87500;2.16507;,
 -4.33013;-1.87500;0.00000;,
 -3.75000;-1.87500;-2.16506;,
 -2.16507;-1.87500;-3.75000;,
 0.00000;-1.87500;-4.33013;,
 1.76777;-2.65165;-3.06186;,
 0.00000;-2.65165;-3.53553;,
 3.06186;-2.65165;-1.76777;,
 3.53553;-2.65165;0.00000;,
 3.06186;-2.65165;1.76777;,
 1.76777;-2.65165;3.06186;,
 0.00000;-2.65165;3.53553;,
 -1.76777;-2.65165;3.06186;,
 -3.06186;-2.65165;1.76777;,
 -3.53553;-2.65165;0.00000;,
 -3.06186;-2.65165;-1.76777;,
 -1.76777;-2.65165;-3.06186;,
 0.00000;-2.65165;-3.53553;,
 1.25000;-3.24760;-2.16506;,
 0.00000;-3.24760;-2.50000;,
 2.16506;-3.24760;-1.25000;,
 2.50000;-3.24760;0.00000;,
 2.16506;-3.24760;1.25000;,
 1.25000;-3.24760;2.16506;,
 0.00000;-3.24760;2.50000;,
 -1.25000;-3.24760;2.16506;,
 -2.16506;-3.24760;1.25000;,
 -2.50000;-3.24760;0.00000;,
 -2.16507;-3.24760;-1.25000;,
 -1.25000;-3.24760;-2.16506;,
 0.00000;-3.24760;-2.50000;,
 0.64705;-3.62222;-1.12072;,
 0.00000;-3.62222;-1.29410;,
 1.12072;-3.62222;-0.64705;,
 1.29410;-3.62222;0.00000;,
 1.12072;-3.62222;0.64705;,
 0.64705;-3.62222;1.12072;,
 0.00000;-3.62222;1.29410;,
 -0.64705;-3.62222;1.12072;,
 -1.12072;-3.62222;0.64705;,
 -1.29410;-3.62222;0.00000;,
 -1.12072;-3.62222;-0.64705;,
 -0.64705;-3.62222;-1.12072;,
 0.00000;-3.62222;-1.29410;,
 0.00000;-3.62222;-1.29410;,
 0.64705;-3.62222;-1.12072;,
 0.00000;-3.75000;-0.00000;,
 1.12072;-3.62222;-0.64705;,
 0.00000;-3.75000;-0.00000;,
 1.29410;-3.62222;0.00000;,
 0.00000;-3.75000;-0.00000;,
 1.12072;-3.62222;0.64705;,
 0.00000;-3.75000;-0.00000;,
 0.64705;-3.62222;1.12072;,
 0.00000;-3.75000;-0.00000;,
 0.00000;-3.62222;1.29410;,
 0.00000;-3.75000;-0.00000;,
 -0.64705;-3.62222;1.12072;,
 0.00000;-3.75000;-0.00000;,
 -1.12072;-3.62222;0.64705;,
 0.00000;-3.75000;-0.00000;,
 -1.29410;-3.62222;0.00000;,
 0.00000;-3.75000;-0.00000;,
 -1.12072;-3.62222;-0.64705;,
 0.00000;-3.75000;-0.00000;,
 -0.64705;-3.62222;-1.12072;,
 0.00000;-3.75000;-0.00000;,
 0.00000;-3.62222;-1.29410;,
 0.00000;-3.75000;-0.00000;;
 
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
 3;155,156,157;,
 3;156,158,159;,
 3;158,160,161;,
 3;160,162,163;,
 3;162,164,165;,
 3;164,166,167;,
 3;166,168,169;,
 3;168,170,171;,
 3;170,172,173;,
 3;172,174,175;,
 3;174,176,177;,
 3;176,178,179;;
 
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  134;
  -0.000000;1.000000;0.000000;,
  -0.000000;0.980132;-0.198347;,
  0.099174;0.980132;-0.171774;,
  0.171774;0.980132;-0.099174;,
  0.198347;0.980132;0.000000;,
  0.171774;0.980132;0.099174;,
  0.099174;0.980132;0.171774;,
  0.000000;0.980132;0.198347;,
  -0.099174;0.980132;0.171774;,
  -0.171774;0.980132;0.099174;,
  -0.198347;0.980132;0.000000;,
  -0.171774;0.980132;-0.099174;,
  -0.099174;0.980132;-0.171774;,
  -0.000000;0.916566;-0.399883;,
  0.199942;0.916566;-0.346309;,
  0.346309;0.916566;-0.199942;,
  0.399883;0.916566;0.000000;,
  0.346309;0.916566;0.199942;,
  0.199942;0.916566;0.346309;,
  0.000000;0.916566;0.399883;,
  -0.199942;0.916566;0.346309;,
  -0.346309;0.916566;0.199942;,
  -0.399884;0.916566;0.000000;,
  -0.346309;0.916566;-0.199942;,
  -0.199942;0.916566;-0.346309;,
  -0.000000;0.797557;-0.603244;,
  0.301622;0.797557;-0.522425;,
  0.522425;0.797557;-0.301622;,
  0.603244;0.797557;-0.000000;,
  0.522425;0.797557;0.301622;,
  0.301622;0.797557;0.522425;,
  0.000000;0.797557;0.603244;,
  -0.301622;0.797557;0.522425;,
  -0.522424;0.797557;0.301622;,
  -0.603244;0.797557;0.000000;,
  -0.522425;0.797557;-0.301622;,
  -0.301622;0.797557;-0.522424;,
  -0.000000;0.606308;-0.795230;,
  0.397615;0.606308;-0.688689;,
  0.688689;0.606308;-0.397615;,
  0.795230;0.606308;0.000000;,
  0.688689;0.606308;0.397615;,
  0.397615;0.606308;0.688689;,
  0.000000;0.606308;0.795230;,
  -0.397615;0.606308;0.688689;,
  -0.688689;0.606308;0.397615;,
  -0.795230;0.606308;0.000000;,
  -0.688689;0.606308;-0.397614;,
  -0.397615;0.606308;-0.688689;,
  -0.000000;0.333257;-0.942836;,
  0.471418;0.333257;-0.816520;,
  0.816520;0.333257;-0.471418;,
  0.942836;0.333257;0.000000;,
  0.816520;0.333257;0.471418;,
  0.471418;0.333257;0.816520;,
  0.000000;0.333257;0.942836;,
  -0.471418;0.333257;0.816520;,
  -0.816520;0.333257;0.471418;,
  -0.942836;0.333257;0.000000;,
  -0.816520;0.333257;-0.471417;,
  -0.471418;0.333257;-0.816520;,
  -0.000000;-0.000000;-1.000000;,
  0.500000;-0.000000;-0.866025;,
  0.866025;-0.000000;-0.500000;,
  1.000000;-0.000000;0.000000;,
  0.866025;-0.000000;0.500000;,
  0.500000;-0.000000;0.866025;,
  0.000000;-0.000000;1.000000;,
  -0.500000;-0.000000;0.866026;,
  -0.866025;-0.000001;0.500000;,
  -1.000000;-0.000000;0.000001;,
  -0.866026;-0.000000;-0.499999;,
  -0.500000;-0.000000;-0.866025;,
  -0.000000;-0.333256;-0.942836;,
  0.471418;-0.333256;-0.816520;,
  0.816520;-0.333256;-0.471418;,
  0.942836;-0.333256;0.000000;,
  0.816520;-0.333257;0.471418;,
  0.471418;-0.333256;0.816520;,
  0.000000;-0.333256;0.942836;,
  -0.471418;-0.333256;0.816520;,
  -0.816520;-0.333256;0.471418;,
  -0.942836;-0.333256;0.000001;,
  -0.816520;-0.333256;-0.471418;,
  -0.471418;-0.333256;-0.816520;,
  -0.000000;-0.606307;-0.795231;,
  0.397615;-0.606307;-0.688690;,
  0.688690;-0.606307;-0.397615;,
  0.795231;-0.606307;0.000000;,
  0.688690;-0.606307;0.397615;,
  0.397615;-0.606307;0.688690;,
  0.000000;-0.606307;0.795231;,
  -0.397615;-0.606307;0.688690;,
  -0.688690;-0.606307;0.397616;,
  -0.795231;-0.606307;0.000000;,
  -0.688690;-0.606307;-0.397615;,
  -0.397616;-0.606307;-0.688690;,
  -0.000000;-0.797557;-0.603244;,
  0.301622;-0.797557;-0.522425;,
  0.522425;-0.797557;-0.301622;,
  0.603244;-0.797557;0.000000;,
  0.522425;-0.797557;0.301622;,
  0.301622;-0.797557;0.522425;,
  0.000000;-0.797557;0.603244;,
  -0.301622;-0.797557;0.522425;,
  -0.522425;-0.797557;0.301622;,
  -0.603244;-0.797557;0.000000;,
  -0.522425;-0.797557;-0.301622;,
  -0.301622;-0.797557;-0.522424;,
  -0.000000;-0.916566;-0.399884;,
  0.199942;-0.916566;-0.346309;,
  0.346309;-0.916566;-0.199942;,
  0.399884;-0.916566;-0.000000;,
  0.346309;-0.916566;0.199942;,
  0.199942;-0.916566;0.346309;,
  0.000000;-0.916566;0.399884;,
  -0.199942;-0.916566;0.346309;,
  -0.346309;-0.916566;0.199942;,
  -0.399884;-0.916566;0.000000;,
  -0.346310;-0.916566;-0.199942;,
  -0.199942;-0.916566;-0.346309;,
  -0.000000;-0.980132;-0.198347;,
  0.099174;-0.980132;-0.171774;,
  0.171774;-0.980132;-0.099174;,
  0.198347;-0.980132;-0.000000;,
  0.171774;-0.980132;0.099174;,
  0.099174;-0.980132;0.171774;,
  0.000000;-0.980132;0.198347;,
  -0.099174;-0.980132;0.171774;,
  -0.171774;-0.980132;0.099174;,
  -0.198347;-0.980132;0.000000;,
  -0.171774;-0.980132;-0.099174;,
  -0.099174;-0.980132;-0.171774;,
  0.000000;-1.000000;0.000000;;
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
  4;6,7,19,18;,
  4;7,8,20,19;,
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
  3;126,127,133;,
  3;127,128,133;,
  3;128,129,133;,
  3;129,130,133;,
  3;130,131,133;,
  3;131,132,133;,
  3;132,121,133;;
 }
 MeshTextureCoords {
  180;
  0.041667;0.000000;,
  0.083333;0.083333;,
  0.000000;0.083333;,
  0.125000;0.000000;,
  0.166667;0.083333;,
  0.208333;0.000000;,
  0.250000;0.083333;,
  0.291667;0.000000;,
  0.333333;0.083333;,
  0.375000;0.000000;,
  0.416667;0.083333;,
  0.458333;0.000000;,
  0.500000;0.083333;,
  0.541667;0.000000;,
  0.583333;0.083333;,
  0.625000;0.000000;,
  0.666667;0.083333;,
  0.708333;0.000000;,
  0.750000;0.083333;,
  0.791667;0.000000;,
  0.833333;0.083333;,
  0.875000;0.000000;,
  0.916667;0.083333;,
  0.958333;0.000000;,
  1.000000;0.083333;,
  0.083333;0.166667;,
  0.000000;0.166667;,
  0.166667;0.166667;,
  0.250000;0.166667;,
  0.333333;0.166667;,
  0.416667;0.166667;,
  0.500000;0.166667;,
  0.583333;0.166667;,
  0.666667;0.166667;,
  0.750000;0.166667;,
  0.833333;0.166667;,
  0.916667;0.166667;,
  1.000000;0.166667;,
  0.083333;0.250000;,
  0.000000;0.250000;,
  0.166667;0.250000;,
  0.250000;0.250000;,
  0.333333;0.250000;,
  0.416667;0.250000;,
  0.500000;0.250000;,
  0.583333;0.250000;,
  0.666667;0.250000;,
  0.750000;0.250000;,
  0.833333;0.250000;,
  0.916667;0.250000;,
  1.000000;0.250000;,
  0.083333;0.333333;,
  0.000000;0.333333;,
  0.166667;0.333333;,
  0.250000;0.333333;,
  0.333333;0.333333;,
  0.416667;0.333333;,
  0.500000;0.333333;,
  0.583333;0.333333;,
  0.666667;0.333333;,
  0.750000;0.333333;,
  0.833333;0.333333;,
  0.916667;0.333333;,
  1.000000;0.333333;,
  0.083333;0.416667;,
  0.000000;0.416667;,
  0.166667;0.416667;,
  0.250000;0.416667;,
  0.333333;0.416667;,
  0.416667;0.416667;,
  0.500000;0.416667;,
  0.583333;0.416667;,
  0.666667;0.416667;,
  0.750000;0.416667;,
  0.833333;0.416667;,
  0.916667;0.416667;,
  1.000000;0.416667;,
  0.083333;0.500000;,
  0.000000;0.500000;,
  0.166667;0.500000;,
  0.250000;0.500000;,
  0.333333;0.500000;,
  0.416667;0.500000;,
  0.500000;0.500000;,
  0.583333;0.500000;,
  0.666667;0.500000;,
  0.750000;0.500000;,
  0.833333;0.500000;,
  0.916667;0.500000;,
  1.000000;0.500000;,
  0.083333;0.583333;,
  0.000000;0.583333;,
  0.166667;0.583333;,
  0.250000;0.583333;,
  0.333333;0.583333;,
  0.416667;0.583333;,
  0.500000;0.583333;,
  0.583333;0.583333;,
  0.666667;0.583333;,
  0.750000;0.583333;,
  0.833333;0.583333;,
  0.916667;0.583333;,
  1.000000;0.583333;,
  0.083333;0.666667;,
  0.000000;0.666667;,
  0.166667;0.666667;,
  0.250000;0.666667;,
  0.333333;0.666667;,
  0.416667;0.666667;,
  0.500000;0.666667;,
  0.583333;0.666667;,
  0.666667;0.666667;,
  0.750000;0.666667;,
  0.833333;0.666667;,
  0.916667;0.666667;,
  1.000000;0.666667;,
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
  0.083333;0.833333;,
  0.000000;0.833333;,
  0.166667;0.833333;,
  0.250000;0.833333;,
  0.333333;0.833333;,
  0.416667;0.833333;,
  0.500000;0.833333;,
  0.583333;0.833333;,
  0.666667;0.833333;,
  0.750000;0.833333;,
  0.833333;0.833333;,
  0.916667;0.833333;,
  1.000000;0.833333;,
  0.083333;0.916667;,
  0.000000;0.916667;,
  0.166667;0.916667;,
  0.250000;0.916667;,
  0.333333;0.916667;,
  0.416667;0.916667;,
  0.500000;0.916667;,
  0.583333;0.916667;,
  0.666667;0.916667;,
  0.750000;0.916667;,
  0.833333;0.916667;,
  0.916667;0.916667;,
  1.000000;0.916667;,
  0.000000;0.916667;,
  0.083333;0.916667;,
  0.041667;1.000000;,
  0.166667;0.916667;,
  0.125000;1.000000;,
  0.250000;0.916667;,
  0.208333;1.000000;,
  0.333333;0.916667;,
  0.291667;1.000000;,
  0.416667;0.916667;,
  0.375000;1.000000;,
  0.500000;0.916667;,
  0.458333;1.000000;,
  0.583333;0.916667;,
  0.541667;1.000000;,
  0.666667;0.916667;,
  0.625000;1.000000;,
  0.750000;0.916667;,
  0.708333;1.000000;,
  0.833333;0.916667;,
  0.791667;1.000000;,
  0.916667;0.916667;,
  0.875000;1.000000;,
  1.000000;0.916667;,
  0.958333;1.000000;;
 }
}
