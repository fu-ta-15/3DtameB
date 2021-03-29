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
 392;
 -1.38003;4.31516;-0.49556;,
 0.44090;4.31516;-0.49556;,
 0.44090;-1.55301;-0.49556;,
 -1.38003;-1.55301;-0.49556;,
 0.44090;-7.42122;-0.49556;,
 -1.38003;-7.42122;-0.49556;,
 0.44090;-13.28937;-0.49556;,
 -1.38003;-13.28937;-0.49556;,
 0.48066;69.87341;0.01891;,
 0.48066;69.87341;0.05146;,
 1.19401;62.99705;0.03628;,
 1.19401;62.99705;-0.02418;,
 1.19401;57.12896;0.06991;,
 1.19401;57.12896;-0.06991;,
 1.19401;51.26067;0.06991;,
 1.19401;51.26067;-0.06991;,
 1.19401;45.39251;0.06991;,
 1.19401;45.39251;-0.06991;,
 1.19401;39.52430;0.06991;,
 1.19401;39.52430;-0.06991;,
 1.19401;33.65612;0.06991;,
 1.19401;33.65612;-0.06991;,
 1.19401;27.78791;0.06991;,
 1.19401;27.78791;-0.06991;,
 1.19401;21.91972;0.06991;,
 1.19401;21.91972;-0.06991;,
 1.19401;16.05154;0.06991;,
 1.19401;16.05154;-0.06991;,
 0.44090;10.18335;0.49556;,
 0.44090;10.18335;-0.49556;,
 0.44090;4.31516;-0.49556;,
 0.44090;4.31516;0.49556;,
 0.44090;-1.55301;0.49556;,
 0.44090;-1.55301;-0.49556;,
 0.44090;-7.42122;0.49556;,
 0.44090;-7.42122;-0.49556;,
 0.44090;-13.28937;0.49556;,
 0.44090;-13.28937;-0.49556;,
 0.44090;4.31516;0.49556;,
 -1.38003;4.31516;0.49556;,
 -1.38003;-1.55301;0.49556;,
 0.44090;-1.55301;0.49556;,
 -1.38003;-7.42122;0.49556;,
 0.44090;-7.42122;0.49556;,
 -1.38003;-13.28937;0.49556;,
 0.44090;-13.28937;0.49556;,
 -1.38003;62.99705;0.47191;,
 -1.38003;62.99705;-0.47191;,
 -1.38003;57.12896;-0.47191;,
 -1.38003;57.12896;0.47191;,
 -1.38003;51.26067;-0.47191;,
 -1.38003;51.26067;0.47191;,
 -1.38003;45.39251;-0.47191;,
 -1.38003;45.39251;0.47191;,
 -1.38003;39.52430;-0.47191;,
 -1.38003;39.52430;0.47191;,
 -1.38003;33.65612;-0.47191;,
 -1.38003;33.65612;0.47191;,
 -1.38003;27.78791;-0.47191;,
 -1.38003;27.78791;0.47191;,
 -1.38003;21.91972;-0.47191;,
 -1.38003;21.91972;0.47191;,
 -1.38003;16.05154;-0.47191;,
 -1.38003;16.05154;0.47191;,
 -1.38003;10.18335;-0.47191;,
 -1.38003;10.18335;0.47191;,
 -1.38003;4.31516;0.49556;,
 -1.38003;4.31516;-0.49556;,
 -1.38003;-1.55301;-0.49556;,
 -1.38003;-1.55301;0.49556;,
 -1.38003;-7.42122;-0.49556;,
 -1.38003;-7.42122;0.49556;,
 -1.38003;-13.28937;-0.49556;,
 -1.38003;-13.28937;0.49556;,
 -1.37611;76.56050;-0.00601;,
 0.48066;69.87341;0.01891;,
 1.19401;62.99705;-0.02418;,
 0.41908;62.99705;-0.46273;,
 -1.36754;76.52960;0.01423;,
 0.42798;62.99705;0.45672;,
 1.19401;62.99705;0.03628;,
 0.48066;69.87341;0.05146;,
 -1.36754;76.52960;0.01423;,
 0.48066;69.87341;0.01891;,
 -1.37611;76.56050;-0.00601;,
 -1.38003;76.57459;-0.00607;,
 -1.38003;76.57459;0.01398;,
 0.42400;62.99705;-0.42529;,
 1.19401;57.12896;-0.06991;,
 0.42461;57.12896;-0.45725;,
 -1.38003;57.12896;-0.47191;,
 -1.38003;62.99705;-0.47191;,
 1.19401;51.26067;-0.06991;,
 0.42541;51.26067;-0.45713;,
 -1.38003;51.26067;-0.47191;,
 1.19401;45.39251;-0.06991;,
 0.42621;45.39251;-0.45700;,
 -1.38003;45.39251;-0.47191;,
 1.19401;39.52430;-0.06991;,
 0.42700;39.52430;-0.45685;,
 -1.38003;39.52430;-0.47191;,
 1.19401;33.65612;-0.06991;,
 0.42781;33.65612;-0.45673;,
 -1.38003;33.65612;-0.47191;,
 1.19401;27.78791;-0.06991;,
 0.42861;27.78791;-0.45659;,
 -1.38003;27.78791;-0.47191;,
 1.19401;21.91972;-0.06991;,
 0.42940;21.91972;-0.45647;,
 -1.38003;21.91972;-0.47191;,
 1.19401;16.05154;-0.06991;,
 0.43021;16.05154;-0.45632;,
 -1.38003;16.05154;-0.47191;,
 0.44090;10.18335;-0.49556;,
 0.42915;10.18335;-0.49556;,
 -1.38003;10.18335;-0.47191;,
 0.42611;62.99705;0.43340;,
 -1.38003;62.99705;0.47191;,
 -1.38003;57.12896;0.47191;,
 0.42705;57.12896;0.45685;,
 1.19401;57.12896;0.06991;,
 -1.38003;51.26067;0.47191;,
 0.42786;51.26067;0.45672;,
 1.19401;51.26067;0.06991;,
 -1.38003;45.39251;0.47191;,
 0.42865;45.39251;0.45659;,
 1.19401;45.39251;0.06991;,
 -1.38003;39.52430;0.47191;,
 0.42945;39.52430;0.45646;,
 1.19401;39.52430;0.06991;,
 -1.38003;33.65612;0.47191;,
 0.43025;33.65612;0.45632;,
 1.19401;33.65612;0.06991;,
 -1.38003;27.78791;0.47191;,
 0.43105;27.78791;0.45619;,
 1.19401;27.78791;0.06991;,
 -1.38003;21.91972;0.47191;,
 0.43184;21.91972;0.45605;,
 1.19401;21.91972;0.06991;,
 -1.38003;16.05154;0.47191;,
 0.43264;16.05154;0.45593;,
 1.19401;16.05154;0.06991;,
 -1.38003;10.18335;0.47191;,
 0.43531;10.18335;0.49556;,
 0.44090;10.18335;0.49556;,
 0.42787;62.99705;0.45672;,
 0.42787;62.99784;0.45668;,
 0.44090;7.27247;-0.49556;,
 -1.38003;7.27242;-0.48364;,
 0.44090;7.27017;0.49556;,
 0.44090;7.27247;-0.49556;,
 -1.38003;7.27017;0.48365;,
 0.44090;7.27017;0.49556;,
 -1.38003;7.27242;-0.48364;,
 -1.38003;7.27017;0.48365;,
 0.44090;6.78059;-0.49556;,
 -1.38003;6.76772;-0.48568;,
 0.44090;6.78687;0.49556;,
 0.44090;6.78059;-0.49556;,
 -1.38003;6.77390;0.48565;,
 0.44090;6.78687;0.49556;,
 -1.38003;6.76772;-0.48568;,
 -1.38003;6.77390;0.48565;,
 0.44090;6.21408;-0.49556;,
 -1.38003;6.22684;-0.48786;,
 0.44090;6.23013;0.49556;,
 0.44090;6.21408;-0.49556;,
 -1.38003;6.24263;0.48779;,
 0.44090;6.23013;0.49556;,
 -1.38003;6.22684;-0.48786;,
 -1.38003;6.24263;0.48779;,
 -1.16386;-13.28937;-0.49556;,
 -1.15184;-13.28937;0.49556;,
 -1.38003;-13.28937;-0.49556;,
 -0.07595;-13.28937;-0.49556;,
 0.44090;-13.28937;-0.49556;,
 -0.08292;-13.28937;0.49556;,
 -0.61149;-13.28937;0.49556;,
 -0.62890;-13.28937;-0.49556;,
 -1.38003;69.80579;-0.23830;,
 -1.38003;69.81563;0.24194;,
 -1.38003;76.57459;-0.00607;,
 -0.34578;69.83350;-0.23254;,
 -1.38003;69.80579;-0.23830;,
 -1.38003;76.57459;-0.00607;,
 -0.48039;69.84331;0.23286;,
 -1.38003;76.57459;0.01398;,
 -0.34373;69.84320;0.23348;,
 -1.38003;69.81563;0.24194;,
 -1.40338;15.90081;-0.66307;,
 2.26144;15.90081;-0.66307;,
 1.38520;11.88302;-0.66307;,
 -1.52648;11.88302;-0.66307;,
 -1.52648;3.84748;-0.66307;,
 1.34046;3.84748;-0.66307;,
 1.34046;-0.17029;-0.66307;,
 -1.52648;-0.17029;-0.66307;,
 1.34046;-4.18806;-0.66307;,
 -1.52648;-4.18806;-0.66307;,
 1.34046;-8.20579;-0.66307;,
 -1.52648;-8.20579;-0.66307;,
 1.34046;-12.22358;-0.66307;,
 -1.52648;-12.22358;-0.66307;,
 2.26144;15.90081;-0.66307;,
 2.33370;15.90081;0.00000;,
 1.38520;11.88302;0.00000;,
 1.38520;11.88302;-0.66307;,
 2.26144;15.90081;0.66307;,
 1.38520;11.88302;0.66307;,
 1.34046;3.84748;-0.66307;,
 1.34046;3.84748;0.00000;,
 1.34046;-0.17029;-0.00000;,
 1.34046;-0.17029;-0.66307;,
 1.34046;3.84748;0.66307;,
 1.34046;-0.17029;0.66307;,
 1.34046;-4.18806;-0.00000;,
 1.34046;-4.18806;-0.66307;,
 1.34046;-4.18806;0.66307;,
 1.34046;-8.20579;-0.00000;,
 1.34046;-8.20579;-0.66307;,
 1.34046;-8.20579;0.66307;,
 1.34046;-12.22358;-0.00000;,
 1.34046;-12.22358;-0.66307;,
 1.34046;-12.22358;0.66307;,
 1.34046;-15.56074;-0.00000;,
 1.34046;-15.56074;-0.66307;,
 1.34046;-15.56074;0.66307;,
 2.26144;15.90081;0.66307;,
 -1.40338;15.90081;0.66307;,
 -1.52648;11.88302;0.66307;,
 1.38520;11.88302;0.66307;,
 1.34046;3.84748;0.66307;,
 -1.52648;3.84748;0.66307;,
 -1.52648;-0.17029;0.66307;,
 1.34046;-0.17029;0.66307;,
 -1.52648;-4.18806;0.66307;,
 1.34046;-4.18806;0.66307;,
 -1.52648;-8.20579;0.66307;,
 1.34046;-8.20579;0.66307;,
 -1.52648;-12.22358;0.66307;,
 1.34046;-12.22358;0.66307;,
 -1.40338;15.90081;0.66307;,
 -1.40338;15.90081;0.00000;,
 -1.52648;11.88302;0.00000;,
 -1.52648;11.88302;0.66307;,
 -1.40338;15.90081;-0.66307;,
 -1.52648;11.88302;-0.66307;,
 -1.52648;3.84748;0.66307;,
 -1.52648;3.84748;0.00000;,
 -1.52648;-0.17029;0.00000;,
 -1.52648;-0.17029;0.66307;,
 -1.52648;3.84748;-0.66307;,
 -1.52648;-0.17029;-0.66307;,
 -1.52648;-4.18806;0.00000;,
 -1.52648;-4.18806;0.66307;,
 -1.52648;-4.18806;-0.66307;,
 -1.52648;-8.20579;0.00000;,
 -1.52648;-8.20579;0.66307;,
 -1.52648;-8.20579;-0.66307;,
 -1.52648;-12.22358;0.00000;,
 -1.52648;-12.22358;0.66307;,
 -1.52648;-12.22358;-0.66307;,
 -1.52648;-15.56074;0.00000;,
 -1.52648;-15.56074;0.66307;,
 -1.52648;-15.56074;-0.66307;,
 2.33370;15.90081;0.00000;,
 -1.40338;15.90081;0.00000;,
 2.26144;15.90081;-0.66307;,
 -1.40338;15.90081;-0.66307;,
 0.96853;11.02260;-0.66307;,
 -1.52648;11.07092;-0.66307;,
 0.96853;10.96363;0.00000;,
 0.96853;11.02260;-0.66307;,
 0.96853;10.90468;0.66307;,
 -1.52648;10.95298;0.66307;,
 0.96853;10.90468;0.66307;,
 -1.52648;11.01196;0.00000;,
 -1.52648;10.95298;0.66307;,
 -1.52648;11.07092;-0.66307;,
 0.86341;10.29531;-0.66307;,
 -1.52648;10.34754;-0.66307;,
 0.86341;10.23292;0.00000;,
 0.86341;10.29531;-0.66307;,
 0.86341;10.17054;0.66307;,
 -1.52648;10.22278;0.66307;,
 0.86341;10.17054;0.66307;,
 -1.52648;10.28515;0.00000;,
 -1.52648;10.22278;0.66307;,
 -1.52648;10.34754;-0.66307;,
 0.81199;9.49962;-0.66307;,
 -1.52648;9.50326;-0.66307;,
 0.81199;9.43349;0.00000;,
 0.81199;9.49962;-0.66307;,
 0.81199;9.36738;0.66307;,
 -1.52648;9.37103;0.66307;,
 0.81199;9.36738;0.66307;,
 -1.52648;9.43714;0.00000;,
 -1.52648;9.37103;0.66307;,
 -1.52648;9.50326;-0.66307;,
 0.84180;8.66071;-0.66307;,
 0.94212;7.86525;-0.66307;,
 -1.52648;7.86525;-0.66307;,
 -1.52648;8.71277;-0.66307;,
 0.84180;8.59067;0.00000;,
 0.94212;7.86525;0.00000;,
 0.94212;7.86525;-0.66307;,
 0.84180;8.66071;-0.66307;,
 0.84180;8.52065;0.66307;,
 0.94212;7.86525;0.66307;,
 -1.52648;8.57269;0.66307;,
 -1.52648;7.86525;0.66307;,
 0.94212;7.86525;0.66307;,
 0.84180;8.52065;0.66307;,
 -1.52648;8.64274;0.00000;,
 -1.52648;7.86525;0.00000;,
 -1.52648;7.86525;0.66307;,
 -1.52648;8.57269;0.66307;,
 -1.52648;8.71277;-0.66307;,
 -1.52648;7.86525;-0.66307;,
 1.11441;7.27287;-0.66307;,
 -1.52648;7.27282;-0.66307;,
 1.11441;7.27133;0.00000;,
 1.11441;7.27287;-0.66307;,
 1.11441;7.26976;0.66307;,
 -1.52648;7.26972;0.66307;,
 1.11441;7.26976;0.66307;,
 -1.52648;7.27131;0.00000;,
 -1.52648;7.26972;0.66307;,
 -1.52648;7.27282;-0.66307;,
 1.34046;6.78591;-0.66307;,
 -1.52648;6.76557;-0.66307;,
 1.34046;6.79011;0.00000;,
 1.34046;6.78591;-0.66307;,
 1.34046;6.79431;0.66307;,
 -1.52648;6.77397;0.66307;,
 1.34046;6.79431;0.66307;,
 -1.52648;6.76977;0.00000;,
 -1.52648;6.77397;0.66307;,
 -1.52648;6.76557;-0.66307;,
 1.34046;6.20515;-0.66307;,
 -1.52648;6.22504;-0.66307;,
 1.34046;6.21587;0.00000;,
 1.34046;6.20515;-0.66307;,
 1.34046;6.22659;0.66307;,
 -1.52648;6.24650;0.66307;,
 1.34046;6.22659;0.66307;,
 -1.52648;6.23576;0.00000;,
 -1.52648;6.24650;0.66307;,
 -1.52648;6.22504;-0.66307;,
 0.99898;-12.22358;-0.66307;,
 1.34046;-15.56074;-0.66307;,
 1.00005;-16.17167;-0.66307;,
 0.96464;-12.22358;0.66307;,
 0.96571;-16.17167;0.66307;,
 1.34046;-15.56074;0.66307;,
 0.98288;-16.17167;-0.00000;,
 1.34046;-15.56074;-0.00000;,
 0.96571;-16.17167;0.66307;,
 1.00005;-16.17167;-0.66307;,
 1.34046;-15.56074;-0.66307;,
 -1.16777;-16.17167;-0.66307;,
 -1.52648;-15.56074;-0.66307;,
 -1.16522;-12.22358;-0.66307;,
 -1.14913;-12.22358;0.66307;,
 -1.52648;-15.56074;0.66307;,
 -1.15167;-16.17167;0.66307;,
 -1.15167;-16.17167;0.66307;,
 -1.52648;-15.56074;0.00000;,
 -1.15972;-16.17167;0.00000;,
 -1.52648;-15.56074;-0.66307;,
 -1.16777;-16.17167;-0.66307;,
 0.48107;-12.22358;-0.66307;,
 0.48114;-16.51468;-0.66307;,
 -0.07530;-16.60062;-0.66307;,
 -0.07458;-12.22358;-0.66307;,
 0.47852;-16.51468;0.66307;,
 0.47846;-12.22358;0.66307;,
 -0.08390;-12.22358;0.66307;,
 -0.08463;-16.60062;0.66307;,
 0.47983;-16.51468;-0.00000;,
 0.47852;-16.51468;0.66307;,
 -0.08463;-16.60062;0.66307;,
 -0.07997;-16.60062;0.00000;,
 0.48114;-16.51468;-0.66307;,
 -0.07530;-16.60062;-0.66307;,
 -0.63222;-16.51468;-0.66307;,
 -0.63170;-12.22358;-0.66307;,
 -0.60840;-12.22358;0.66307;,
 -0.60892;-16.51468;0.66307;,
 -0.60892;-16.51468;0.66307;,
 -0.62057;-16.51468;0.00000;,
 -0.63222;-16.51468;-0.66307;;
 
 214;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;8,9,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;25,24,26,27;,
 4;27,26,28,29;,
 4;30,31,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;38,39,40,41;,
 4;41,40,42,43;,
 4;43,42,44,45;,
 4;46,47,48,49;,
 4;49,48,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;55,54,56,57;,
 4;57,56,58,59;,
 4;59,58,60,61;,
 4;61,60,62,63;,
 4;63,62,64,65;,
 4;66,67,68,69;,
 4;69,68,70,71;,
 4;71,70,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,9,83,84;,
 4;82,84,85,86;,
 4;87,76,88,89;,
 4;87,89,90,91;,
 4;89,88,92,93;,
 4;89,93,94,90;,
 4;93,92,95,96;,
 4;93,96,97,94;,
 4;96,95,98,99;,
 4;96,99,100,97;,
 4;99,98,101,102;,
 4;99,102,103,100;,
 4;102,101,104,105;,
 4;102,105,106,103;,
 4;105,104,107,108;,
 4;105,108,109,106;,
 4;108,107,110,111;,
 4;108,111,112,109;,
 4;111,110,113,114;,
 4;111,114,115,112;,
 4;116,117,118,119;,
 4;116,119,120,80;,
 4;119,118,121,122;,
 4;119,122,123,120;,
 4;122,121,124,125;,
 4;122,125,126,123;,
 4;125,124,127,128;,
 4;125,128,129,126;,
 4;128,127,130,131;,
 4;128,131,132,129;,
 4;131,130,133,134;,
 4;131,134,135,132;,
 4;134,133,136,137;,
 4;134,137,138,135;,
 4;137,136,139,140;,
 4;137,140,141,138;,
 4;140,139,142,143;,
 4;140,143,144,141;,
 3;145,79,146;,
 4;147,148,115,113;,
 4;149,150,29,28;,
 4;151,152,144,142;,
 4;153,154,65,64;,
 4;155,156,148,147;,
 4;157,158,150,149;,
 4;159,160,152,151;,
 4;161,162,154,153;,
 4;163,1,0,164;,
 4;163,164,156,155;,
 4;165,31,30,166;,
 4;165,166,158,157;,
 4;167,39,38,168;,
 4;167,168,160,159;,
 4;169,67,66,170;,
 4;169,170,162,161;,
 4;171,172,73,173;,
 4;174,175,36,176;,
 4;177,172,171,178;,
 4;177,178,174,176;,
 4;179,47,46,180;,
 4;179,180,86,181;,
 4;182,77,91,183;,
 4;182,183,184,74;,
 4;185,78,186,187;,
 4;185,187,145,146;,
 3;187,186,188;,
 4;187,188,117,145;,
 4;189,190,191,192;,
 4;193,194,195,196;,
 4;196,195,197,198;,
 4;198,197,199,200;,
 4;200,199,201,202;,
 4;203,204,205,206;,
 4;204,207,208,205;,
 4;209,210,211,212;,
 4;210,213,214,211;,
 4;212,211,215,216;,
 4;211,214,217,215;,
 4;216,215,218,219;,
 4;215,217,220,218;,
 4;219,218,221,222;,
 4;218,220,223,221;,
 4;222,221,224,225;,
 4;221,223,226,224;,
 4;227,228,229,230;,
 4;231,232,233,234;,
 4;234,233,235,236;,
 4;236,235,237,238;,
 4;238,237,239,240;,
 4;241,242,243,244;,
 4;242,245,246,243;,
 4;247,248,249,250;,
 4;248,251,252,249;,
 4;250,249,253,254;,
 4;249,252,255,253;,
 4;254,253,256,257;,
 4;253,255,258,256;,
 4;257,256,259,260;,
 4;256,258,261,259;,
 4;260,259,262,263;,
 4;259,261,264,262;,
 4;241,207,265,266;,
 4;266,265,267,268;,
 4;269,270,192,191;,
 4;271,272,206,205;,
 4;273,271,205,208;,
 4;274,275,230,229;,
 4;276,277,244,243;,
 4;278,276,243,246;,
 4;279,280,270,269;,
 4;281,282,272,271;,
 4;283,281,271,273;,
 4;284,285,275,274;,
 4;286,287,277,276;,
 4;288,286,276,278;,
 4;289,290,280,279;,
 4;291,292,282,281;,
 4;293,291,281,283;,
 4;294,295,285,284;,
 4;296,297,287,286;,
 4;298,296,286,288;,
 4;299,300,301,302;,
 4;299,302,290,289;,
 4;303,304,305,306;,
 4;303,306,292,291;,
 4;307,308,304,303;,
 4;307,303,291,293;,
 4;309,310,311,312;,
 4;309,312,295,294;,
 4;313,314,315,316;,
 4;313,316,297,296;,
 4;317,318,314,313;,
 4;317,313,296,298;,
 4;319,320,301,300;,
 4;321,322,305,304;,
 4;323,321,304,308;,
 4;324,325,311,310;,
 4;326,327,315,314;,
 4;328,326,314,318;,
 4;329,330,320,319;,
 4;331,332,322,321;,
 4;333,331,321,323;,
 4;334,335,325,324;,
 4;336,337,327,326;,
 4;338,336,326,328;,
 4;339,194,193,340;,
 4;339,340,330,329;,
 4;341,210,209,342;,
 4;341,342,332,331;,
 4;343,213,210,341;,
 4;343,341,331,333;,
 4;344,232,231,345;,
 4;344,345,335,334;,
 4;346,248,247,347;,
 4;346,347,337,336;,
 4;348,251,248,346;,
 4;348,346,336,338;,
 4;349,201,350,351;,
 4;352,353,354,240;,
 4;355,356,226,357;,
 4;358,359,356,355;,
 4;360,361,202,362;,
 4;363,239,364,365;,
 4;366,263,367,368;,
 4;368,367,369,370;,
 4;371,349,351,372;,
 4;371,372,373,374;,
 4;375,353,352,376;,
 4;375,376,377,378;,
 4;379,355,357,380;,
 4;379,380,381,382;,
 4;383,358,355,379;,
 4;383,379,382,384;,
 4;385,360,362,386;,
 4;385,386,374,373;,
 4;387,363,365,388;,
 4;387,388,378,377;,
 4;389,366,368,390;,
 4;389,390,382,381;,
 4;390,368,370,391;,
 4;390,391,384,382;;
 
 MeshMaterialList {
  2;
  214;
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\texture003.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\チーム制作用\\texture002.jpg";
   }
  }
 }
 MeshNormals {
  149;
  0.963481;0.267776;0.000143;,
  -1.000000;0.000000;0.000000;,
  -0.001051;0.001007;-0.999999;,
  0.000000;0.000000;-1.000000;,
  0.982547;0.186016;0.000054;,
  0.998665;0.051662;0.000000;,
  1.000000;0.000000;0.000000;,
  0.997964;-0.063776;-0.000000;,
  0.976543;0.208034;-0.055540;,
  -0.001061;0.001009;0.999999;,
  0.000000;0.000000;1.000000;,
  0.225034;0.048457;-0.973145;,
  0.192613;0.048733;-0.980064;,
  0.336248;0.052840;0.940290;,
  0.170629;0.049814;0.984075;,
  0.242696;0.004432;-0.970092;,
  0.238912;0.002219;-0.971039;,
  0.235208;0.000006;-0.971945;,
  0.235378;0.000005;-0.971904;,
  0.235548;0.000005;-0.971863;,
  0.235719;0.000005;-0.971821;,
  0.235890;0.000005;-0.971780;,
  0.236062;0.000005;-0.971738;,
  0.175668;0.002618;-0.984446;,
  0.115713;0.005171;-0.993269;,
  0.241144;0.003270;0.970484;,
  0.238396;0.001638;0.971167;,
  0.235730;0.000005;0.971819;,
  0.235900;0.000005;0.971777;,
  0.236071;0.000005;0.971736;,
  0.236243;0.000005;0.971694;,
  0.236413;0.000005;0.971653;,
  0.236584;0.000005;0.971611;,
  0.176068;0.002619;0.984374;,
  0.115992;0.005171;0.993237;,
  0.003917;0.039442;0.999214;,
  0.000000;0.045326;0.998972;,
  -0.007880;0.002017;-0.999967;,
  -0.007887;0.002017;0.999967;,
  -0.005403;0.002020;-0.999983;,
  -0.005425;0.002015;0.999983;,
  -0.003459;0.002017;-0.999992;,
  -0.003482;0.002014;0.999992;,
  0.000000;-1.000000;-0.000000;,
  0.038016;0.034254;-0.998690;,
  0.988109;0.128479;-0.084463;,
  0.373450;0.061489;-0.925610;,
  0.415219;0.033747;-0.909095;,
  0.396513;0.028673;0.917581;,
  0.972938;0.228089;-0.036976;,
  0.963513;0.267660;0.000125;,
  0.452816;0.002966;-0.891599;,
  0.012569;0.001357;-0.999920;,
  0.010929;0.018480;-0.999770;,
  0.449920;0.000021;-0.893069;,
  0.008190;-0.000010;-0.999967;,
  0.450170;0.000020;-0.892943;,
  0.008259;-0.000011;-0.999966;,
  0.450419;0.000021;-0.892817;,
  0.008330;-0.000011;-0.999965;,
  0.450671;0.000021;-0.892690;,
  0.008400;-0.000011;-0.999965;,
  0.450924;0.000021;-0.892563;,
  0.008469;-0.000011;-0.999964;,
  0.451177;0.000021;-0.892435;,
  0.008538;-0.000011;-0.999964;,
  0.344027;0.003497;-0.938953;,
  0.003171;0.001666;-0.999994;,
  0.111968;0.004504;-0.993702;,
  -0.006000;0.002678;-0.999978;,
  0.011331;0.017780;0.999778;,
  0.011597;0.000994;0.999932;,
  0.452735;0.002196;0.891643;,
  0.008403;-0.000011;0.999965;,
  0.450688;0.000021;0.892682;,
  0.008472;-0.000011;0.999964;,
  0.450939;0.000021;0.892555;,
  0.008541;-0.000011;0.999964;,
  0.451192;0.000021;0.892427;,
  0.008610;-0.000011;0.999963;,
  0.451445;0.000021;0.892299;,
  0.008681;-0.000011;0.999962;,
  0.451695;0.000020;0.892173;,
  0.008752;-0.000011;0.999962;,
  0.451945;0.000021;0.892046;,
  0.003341;0.001682;0.999993;,
  0.344637;0.003483;0.938730;,
  -0.005936;0.002694;0.999979;,
  0.112187;0.004489;0.993677;,
  0.071115;0.034240;-0.996880;,
  0.992243;0.109953;-0.057995;,
  0.007548;0.033632;0.999406;,
  0.007262;0.033708;0.999405;,
  0.000000;0.000000;-1.000000;,
  -0.964327;-0.264702;0.002697;,
  0.975182;-0.221406;-0.000000;,
  0.947687;-0.319075;-0.008993;,
  0.977984;0.208649;0.003633;,
  1.000000;0.000000;0.000000;,
  0.966511;-0.256560;0.005780;,
  0.965157;-0.261608;0.005753;,
  0.973821;-0.221097;0.052814;,
  0.949486;-0.313305;0.017792;,
  0.977326;0.211707;0.003790;,
  0.963773;-0.266663;0.005726;,
  0.000000;0.000000;1.000000;,
  -0.999531;0.030625;0.000000;,
  -0.999883;0.015314;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.963034;-0.269366;0.002685;,
  -0.963683;-0.267033;0.002691;,
  0.959683;-0.280653;-0.015610;,
  0.961409;-0.274695;-0.015345;,
  0.994596;-0.103369;-0.009631;,
  0.994621;-0.103131;-0.009608;,
  0.999895;-0.014440;-0.001297;,
  0.999895;-0.014406;-0.001294;,
  0.996230;0.086587;0.005282;,
  0.995941;0.089838;0.005435;,
  0.935628;0.352988;-0.000262;,
  0.935283;0.353901;-0.000255;,
  0.975987;0.217828;-0.000434;,
  0.975736;0.218951;-0.000429;,
  0.731102;-0.682199;0.009679;,
  -0.716219;-0.697843;0.006758;,
  -0.002694;-0.999996;0.000750;,
  0.366700;-0.930329;0.004339;,
  -0.354300;-0.935121;0.004477;,
  0.973821;-0.221097;-0.052814;,
  0.945171;-0.324609;-0.035792;,
  -0.999531;0.030625;0.000000;,
  0.000000;1.000000;0.000000;,
  0.957916;-0.286609;-0.015876;,
  0.994571;-0.103608;-0.009655;,
  0.999894;-0.014474;-0.001300;,
  0.978633;0.205587;0.003475;,
  0.996508;0.083337;0.005129;,
  0.935971;0.352076;-0.000269;,
  0.976237;0.216705;-0.000440;,
  0.730037;-0.683339;0.009668;,
  0.732169;-0.681054;0.009689;,
  -0.713999;-0.700114;0.006739;,
  -0.718433;-0.695563;0.006778;,
  0.369906;-0.929059;0.004385;,
  -0.004090;-0.999991;0.000755;,
  0.363494;-0.931587;0.004292;,
  -0.001299;-0.999999;0.000745;,
  -0.354687;-0.934974;0.004472;,
  -0.353912;-0.935268;0.004481;;
  214;
  4;2,2,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,7,7;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;9,9,10,10;,
  4;10,10,10,10;,
  4;10,10,10,10;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;11,46,47,12;,
  4;13,14,48,13;,
  4;49,4,4,50;,
  4;49,50,0,8;,
  4;15,47,51,16;,
  4;15,16,52,53;,
  4;16,51,54,17;,
  4;16,17,55,52;,
  4;17,54,56,18;,
  4;17,18,57,55;,
  4;18,56,58,19;,
  4;18,19,59,57;,
  4;19,58,60,20;,
  4;19,20,61,59;,
  4;20,60,62,21;,
  4;20,21,63,61;,
  4;21,62,64,22;,
  4;21,22,65,63;,
  4;22,64,66,23;,
  4;22,23,67,65;,
  4;23,66,68,24;,
  4;23,24,69,67;,
  4;25,70,71,26;,
  4;25,26,72,48;,
  4;26,71,73,27;,
  4;26,27,74,72;,
  4;27,73,75,28;,
  4;27,28,76,74;,
  4;28,75,77,29;,
  4;28,29,78,76;,
  4;29,77,79,30;,
  4;29,30,80,78;,
  4;30,79,81,31;,
  4;30,31,82,80;,
  4;31,81,83,32;,
  4;31,32,84,82;,
  4;32,83,85,33;,
  4;32,33,86,84;,
  4;33,85,87,34;,
  4;33,34,88,86;,
  3;35,14,36;,
  4;37,37,69,68;,
  4;6,6,7,7;,
  4;38,38,88,87;,
  4;1,1,1,1;,
  4;39,39,37,37;,
  4;6,6,6,6;,
  4;40,40,38,38;,
  4;1,1,1,1;,
  4;41,2,2,41;,
  4;41,41,39,39;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;42,9,9,42;,
  4;42,42,40,40;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;43,43,43,43;,
  4;43,43,43,43;,
  4;43,43,43,43;,
  4;43,43,43,43;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;44,12,53,44;,
  4;44,44,89,11;,
  4;45,49,8,45;,
  4;45,45,90,90;,
  3;91,92,91;,
  4;91,91,70,35;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;128,95,96,129;,
  4;95,101,102,96;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;98,98,98,98;,
  4;98,98,100,99;,
  4;98,98,104,100;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;130,106,107,107;,
  4;106,130,107,107;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,110,109;,
  4;108,108,94,110;,
  4;131,131,131,131;,
  4;131,131,131,131;,
  4;93,93,93,93;,
  4;111,132,129,96;,
  4;112,111,96,102;,
  4;105,105,105,105;,
  4;108,108,107,107;,
  4;108,108,107,107;,
  4;93,93,93,93;,
  4;113,133,132,111;,
  4;114,113,111,112;,
  4;105,105,105,105;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;93,93,93,93;,
  4;115,134,133,113;,
  4;116,115,113,114;,
  4;105,105,105,105;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;117,97,135,136;,
  4;117,136,134,115;,
  4;118,103,97,117;,
  4;118,117,115,116;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;93,93,93,93;,
  4;119,137,135,97;,
  4;120,119,97,103;,
  4;105,105,105,105;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;93,93,93,93;,
  4;121,138,137,119;,
  4;122,121,119,120;,
  4;105,105,105,105;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;98,98,98,98;,
  4;98,98,138,121;,
  4;98,98,98,98;,
  4;98,98,121,122;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;108,108,108,108;,
  4;93,93,93,93;,
  4;105,105,105,105;,
  4;123,100,104,139;,
  4;140,99,100,123;,
  4;93,93,93,93;,
  4;105,105,105,105;,
  4;141,109,110,124;,
  4;124,110,94,142;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;126,123,139,143;,
  4;126,143,144,125;,
  4;145,140,123,126;,
  4;145,126,125,146;,
  4;93,93,93,93;,
  4;93,93,93,93;,
  4;105,105,105,105;,
  4;105,105,105,105;,
  4;147,141,124,127;,
  4;147,127,125,144;,
  4;127,124,142,148;,
  4;127,148,146,125;;
 }
 MeshTextureCoords {
  392;
  0.000000;0.785710;,
  1.000000;0.785710;,
  1.000000;0.857140;,
  0.000000;0.857140;,
  1.000000;0.928570;,
  0.000000;0.928570;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.071430;,
  0.000000;0.071430;,
  1.000000;0.142860;,
  0.000000;0.142860;,
  1.000000;0.214290;,
  0.000000;0.214290;,
  1.000000;0.285710;,
  0.000000;0.285710;,
  1.000000;0.357140;,
  0.000000;0.357140;,
  1.000000;0.428570;,
  0.000000;0.428570;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.571430;,
  0.000000;0.571430;,
  1.000000;0.642860;,
  0.000000;0.642860;,
  1.000000;0.714290;,
  0.000000;0.714290;,
  0.000000;0.785710;,
  1.000000;0.785710;,
  1.000000;0.857140;,
  0.000000;0.857140;,
  1.000000;0.928570;,
  0.000000;0.928570;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.785710;,
  1.000000;0.785710;,
  1.000000;0.857140;,
  0.000000;0.857140;,
  1.000000;0.928570;,
  0.000000;0.928570;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.071430;,
  1.000000;0.071430;,
  1.000000;0.142860;,
  0.000000;0.142860;,
  1.000000;0.214290;,
  0.000000;0.214290;,
  1.000000;0.285710;,
  0.000000;0.285710;,
  1.000000;0.357140;,
  0.000000;0.357140;,
  1.000000;0.428570;,
  0.000000;0.428570;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.571430;,
  0.000000;0.571430;,
  1.000000;0.642860;,
  0.000000;0.642860;,
  1.000000;0.714290;,
  0.000000;0.714290;,
  0.000000;0.785710;,
  1.000000;0.785710;,
  1.000000;0.857140;,
  0.000000;0.857140;,
  1.000000;0.928570;,
  0.000000;0.928570;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.002100;0.000000;,
  1.000000;0.000000;,
  1.000000;0.071430;,
  0.671600;0.071430;,
  0.993290;0.000000;,
  0.297600;0.071430;,
  0.000000;0.071430;,
  0.000000;0.000000;,
  0.006710;0.000000;,
  1.000000;1.000000;,
  0.002100;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.700860;0.071430;,
  1.000000;0.142860;,
  0.701090;0.142860;,
  0.000000;0.142860;,
  0.000000;0.071430;,
  1.000000;0.214290;,
  0.701400;0.214290;,
  0.000000;0.214290;,
  1.000000;0.285710;,
  0.701710;0.285710;,
  0.000000;0.285710;,
  1.000000;0.357140;,
  0.702020;0.357140;,
  0.000000;0.357140;,
  1.000000;0.428570;,
  0.702330;0.428570;,
  0.000000;0.428570;,
  1.000000;0.500000;,
  0.702650;0.500000;,
  0.000000;0.500000;,
  1.000000;0.571430;,
  0.702950;0.571430;,
  0.000000;0.571430;,
  1.000000;0.642860;,
  0.703270;0.642860;,
  0.000000;0.642860;,
  1.000000;0.714290;,
  0.702860;0.714290;,
  0.000000;0.714290;,
  0.298320;0.071430;,
  1.000000;0.071430;,
  1.000000;0.142860;,
  0.297960;0.142860;,
  0.000000;0.142860;,
  1.000000;0.214290;,
  0.297650;0.214290;,
  0.000000;0.214290;,
  1.000000;0.285710;,
  0.297340;0.285710;,
  0.000000;0.285710;,
  1.000000;0.357140;,
  0.297030;0.357140;,
  0.000000;0.357140;,
  1.000000;0.428570;,
  0.296720;0.428570;,
  0.000000;0.428570;,
  1.000000;0.500000;,
  0.296410;0.500000;,
  0.000000;0.500000;,
  1.000000;0.571430;,
  0.296100;0.571430;,
  0.000000;0.571430;,
  1.000000;0.642860;,
  0.295790;0.642860;,
  0.000000;0.642860;,
  1.000000;0.714290;,
  0.294750;0.714290;,
  0.000000;0.714290;,
  0.297640;0.071430;,
  0.297640;0.071420;,
  1.000000;0.749720;,
  0.000000;0.749720;,
  1.000000;0.749750;,
  0.000000;0.749720;,
  1.000000;0.749750;,
  0.000000;0.749750;,
  1.000000;0.749720;,
  0.000000;0.749750;,
  1.000000;0.755700;,
  0.000000;0.755860;,
  1.000000;0.755630;,
  0.000000;0.755700;,
  1.000000;0.755790;,
  0.000000;0.755630;,
  1.000000;0.755860;,
  0.000000;0.755790;,
  1.000000;0.762600;,
  0.000000;0.762440;,
  1.000000;0.762400;,
  0.000000;0.762600;,
  1.000000;0.762250;,
  0.000000;0.762400;,
  1.000000;0.762440;,
  0.000000;0.762250;,
  0.118710;0.000000;,
  0.125310;1.000000;,
  0.000000;0.000000;,
  0.716160;0.000000;,
  1.000000;0.000000;,
  0.712330;1.000000;,
  0.422060;1.000000;,
  0.412500;0.000000;,
  1.000000;0.035610;,
  0.000000;0.035560;,
  1.000000;0.000000;,
  0.334150;0.035430;,
  0.000000;0.035610;,
  0.000000;0.000000;,
  0.649550;0.035290;,
  1.000000;0.000000;,
  0.651790;0.035410;,
  1.000000;0.035560;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.125000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.375000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.125000;,
  0.000000;0.375000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.875000;,
  0.000000;0.875000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.375000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  0.500000;0.625000;,
  0.000000;0.625000;,
  1.000000;0.625000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.500000;0.875000;,
  0.000000;0.875000;,
  1.000000;0.875000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.151770;,
  0.000000;0.150270;,
  0.500000;0.153600;,
  0.000000;0.151770;,
  1.000000;0.155440;,
  1.000000;0.153940;,
  0.000000;0.155440;,
  0.500000;0.152100;,
  0.000000;0.153940;,
  1.000000;0.150270;,
  1.000000;0.174400;,
  0.000000;0.172770;,
  0.500000;0.176340;,
  0.000000;0.174400;,
  1.000000;0.178280;,
  1.000000;0.176650;,
  0.000000;0.178280;,
  0.500000;0.174710;,
  0.000000;0.176650;,
  1.000000;0.172770;,
  1.000000;0.199150;,
  0.000000;0.199040;,
  0.500000;0.201210;,
  0.000000;0.199150;,
  1.000000;0.203270;,
  1.000000;0.203150;,
  0.000000;0.203270;,
  0.500000;0.201100;,
  0.000000;0.203150;,
  1.000000;0.199040;,
  1.000000;0.225250;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.223630;,
  0.500000;0.227430;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.225250;,
  1.000000;0.229610;,
  1.000000;0.250000;,
  1.000000;0.227990;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.229610;,
  0.500000;0.225810;,
  0.500000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.227990;,
  1.000000;0.223630;,
  1.000000;0.250000;,
  1.000000;0.268430;,
  0.000000;0.268430;,
  0.500000;0.268480;,
  0.000000;0.268430;,
  1.000000;0.268530;,
  1.000000;0.268530;,
  0.000000;0.268530;,
  0.500000;0.268480;,
  0.000000;0.268530;,
  1.000000;0.268430;,
  1.000000;0.283580;,
  0.000000;0.284210;,
  0.500000;0.283450;,
  0.000000;0.283580;,
  1.000000;0.283320;,
  1.000000;0.283950;,
  0.000000;0.283320;,
  0.500000;0.284080;,
  0.000000;0.283950;,
  1.000000;0.284210;,
  1.000000;0.301650;,
  0.000000;0.301030;,
  0.500000;0.301320;,
  0.000000;0.301650;,
  1.000000;0.300980;,
  1.000000;0.300360;,
  0.000000;0.300980;,
  0.500000;0.300700;,
  0.000000;0.300360;,
  1.000000;0.301030;,
  0.880890;0.875000;,
  1.000000;1.000000;,
  0.881260;1.000000;,
  0.131090;0.875000;,
  0.130720;1.000000;,
  0.000000;1.000000;,
  0.875270;0.500000;,
  1.000000;0.500000;,
  0.869280;1.000000;,
  0.881260;0.000000;,
  1.000000;0.000000;,
  0.125120;1.000000;,
  0.000000;1.000000;,
  0.126010;0.875000;,
  0.868380;0.875000;,
  1.000000;1.000000;,
  0.869270;1.000000;,
  0.130730;1.000000;,
  0.000000;0.500000;,
  0.127930;0.500000;,
  0.000000;0.000000;,
  0.125120;0.000000;,
  0.700240;0.875000;,
  0.700260;1.000000;,
  0.506170;1.000000;,
  0.506430;0.875000;,
  0.300650;1.000000;,
  0.300670;0.875000;,
  0.496820;0.875000;,
  0.497080;1.000000;,
  0.699810;0.500000;,
  0.699350;1.000000;,
  0.502920;1.000000;,
  0.504550;0.500000;,
  0.700260;0.000000;,
  0.506170;0.000000;,
  0.311920;1.000000;,
  0.312100;0.875000;,
  0.679770;0.875000;,
  0.679950;1.000000;,
  0.320050;1.000000;,
  0.315980;0.500000;,
  0.311920;0.000000;;
 }
}
