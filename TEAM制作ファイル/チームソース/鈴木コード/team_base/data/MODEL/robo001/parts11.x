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
 26;
 -8.85779;0.91337;-4.47048;,
 -0.20060;5.99090;-5.10694;,
 -0.20060;-2.89251;-5.19767;,
 -9.90961;-6.10374;-4.47048;,
 8.53544;0.91337;-4.47048;,
 9.61355;-6.10374;-4.47048;,
 8.53544;0.91337;-4.47048;,
 8.53544;0.91337;5.23351;,
 9.61355;-6.10374;5.23351;,
 9.61355;-6.10374;-4.47048;,
 8.53544;0.91337;5.23351;,
 -0.20060;5.99090;4.70856;,
 -0.20060;-4.85446;5.34373;,
 9.61355;-6.10374;5.23351;,
 -8.85779;0.91337;5.23351;,
 -9.90961;-6.10374;5.23351;,
 -8.85779;0.91337;5.23351;,
 -8.85779;0.91337;-4.47048;,
 -9.90961;-6.10374;-4.47048;,
 -9.90961;-6.10374;5.23351;,
 -0.20060;5.99090;-5.10694;,
 -8.85779;0.91337;-4.47048;,
 8.53544;0.91337;-4.47048;,
 -9.90961;-6.10374;-4.47048;,
 -0.20060;-2.89251;-5.19767;,
 9.61355;-6.10374;-4.47048;;
 
 10;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;11,14,15,12;,
 4;16,17,18,19;,
 4;16,11,20,21;,
 4;11,7,22,20;,
 4;23,24,12,19;,
 4;24,25,8,12;;
 
 MeshMaterialList {
  1;
  10;
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
  15;
  -0.078905;0.010978;-0.996822;,
  -0.000374;0.011056;-0.999939;,
  0.078160;0.011065;-0.996879;,
  0.826252;0.563301;0.000000;,
  0.000029;0.030115;0.999547;,
  0.988402;0.151858;0.000000;,
  0.007334;0.030108;0.999520;,
  -0.007276;0.030120;0.999520;,
  -0.828389;0.560153;0.000000;,
  -0.988952;0.148238;0.000000;,
  -0.505914;0.862584;0.000000;,
  0.502505;0.864574;0.000000;,
  0.214165;-0.972822;-0.088036;,
  0.001104;-0.995928;-0.090145;,
  -0.212007;-0.973288;-0.088113;;
  10;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;3,3,5,5;,
  4;7,4,4,7;,
  4;4,6,6,4;,
  4;8,8,9,9;,
  4;8,10,10,8;,
  4;11,3,3,11;,
  4;12,13,13,12;,
  4;13,14,14,13;;
 }
 MeshTextureCoords {
  26;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
