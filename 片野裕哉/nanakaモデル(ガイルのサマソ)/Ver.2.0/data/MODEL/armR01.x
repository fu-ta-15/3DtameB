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
 146;
 -0.11029;-0.01935;-0.01798;,
 -0.38818;-0.47032;-1.04349;,
 -0.38819;-0.01935;-1.12800;,
 -0.38818;-0.85266;-0.80287;,
 -0.38818;-1.10811;-0.44275;,
 -0.38819;-1.19782;-0.01798;,
 -0.38818;-1.10811;0.40681;,
 -0.38818;-0.85266;0.76692;,
 -0.38818;-0.47034;1.00755;,
 -0.38819;-0.01935;1.09205;,
 -0.38819;0.43163;1.00755;,
 -0.38818;0.81396;0.76692;,
 -0.38818;1.06943;0.40681;,
 -0.38818;1.15911;-0.01798;,
 -0.38818;1.06943;-0.44275;,
 -0.38818;0.81396;-0.80287;,
 -0.38819;0.43163;-1.04349;,
 -0.66285;-0.53698;-1.19506;,
 -0.66285;-0.01934;-1.29204;,
 -0.66285;-0.97580;-0.91888;,
 -0.66286;-1.26904;-0.50555;,
 -0.66286;-1.37198;-0.01798;,
 -0.66286;-1.26904;0.46959;,
 -0.66285;-0.97580;0.88293;,
 -0.66285;-0.53698;1.15911;,
 -0.66285;-0.01934;1.25610;,
 -0.66285;0.49830;1.15911;,
 -0.66285;0.93713;0.88293;,
 -0.66285;1.23033;0.46959;,
 -0.66285;1.33331;-0.01798;,
 -0.66285;1.23033;-0.50555;,
 -0.66285;0.93713;-0.91888;,
 -0.66285;0.49830;-1.19506;,
 -1.08605;-0.54506;-1.21343;,
 -1.08605;-0.01935;-1.31191;,
 -1.08605;-0.99072;-0.93293;,
 -1.08605;-1.28853;-0.51314;,
 -1.08606;-1.39308;-0.01798;,
 -1.08605;-1.28853;0.47719;,
 -1.08605;-0.99072;0.89698;,
 -1.08605;-0.54506;1.17747;,
 -1.08605;-0.01935;1.27597;,
 -1.08605;0.50637;1.17748;,
 -1.08605;0.95203;0.89698;,
 -1.08605;1.24984;0.47719;,
 -1.08605;1.35442;-0.01798;,
 -1.08605;1.24984;-0.51314;,
 -1.08605;0.95203;-0.93293;,
 -1.08605;0.50637;-1.21343;,
 -2.37221;-0.53984;-1.20156;,
 -2.37221;-0.01935;-1.29907;,
 -2.37222;-0.98108;-0.92385;,
 -2.37221;-1.27593;-0.50822;,
 -2.37222;-1.37944;-0.01798;,
 -2.37221;-1.27593;0.47228;,
 -2.37222;-0.98108;0.88790;,
 -2.37221;-0.53984;1.16560;,
 -2.37221;-0.01935;1.26312;,
 -2.37221;0.50114;1.16561;,
 -2.37221;0.94239;0.88790;,
 -2.37221;1.23723;0.47228;,
 -2.37221;1.34078;-0.01798;,
 -2.37221;1.23723;-0.50822;,
 -2.37221;0.94239;-0.92385;,
 -2.37221;0.50114;-1.20156;,
 -3.65829;-0.52199;-1.16095;,
 -3.65829;-0.01935;-1.25511;,
 -3.65829;-0.94809;-0.89277;,
 -3.65829;-1.23282;-0.49140;,
 -3.65829;-1.33278;-0.01798;,
 -3.65829;-1.23282;0.45546;,
 -3.65829;-0.94809;0.85682;,
 -3.65829;-0.52199;1.12499;,
 -3.65829;-0.01935;1.21917;,
 -3.65829;0.48328;1.12501;,
 -3.65829;0.90939;0.85682;,
 -3.65829;1.19412;0.45546;,
 -3.65830;1.29411;-0.01798;,
 -3.65829;1.19412;-0.49140;,
 -3.65829;0.90939;-0.89277;,
 -3.65829;0.48328;-1.16095;,
 -4.94439;-0.49278;-1.09454;,
 -4.94439;-0.01935;-1.18325;,
 -4.94439;-0.89414;-0.84195;,
 -4.94439;-1.16231;-0.46391;,
 -4.94439;-1.25649;-0.01798;,
 -4.94439;-1.16231;0.42796;,
 -4.94439;-0.89414;0.80599;,
 -4.94439;-0.49278;1.05860;,
 -4.94439;-0.01935;1.14730;,
 -4.94439;0.45409;1.05860;,
 -4.94439;0.85544;0.80599;,
 -4.94439;1.12362;0.42796;,
 -4.94439;1.21780;-0.01798;,
 -4.94439;1.12362;-0.46391;,
 -4.94439;0.85544;-0.84195;,
 -4.94439;0.45409;-1.09454;,
 -6.23054;-0.48343;-1.07328;,
 -6.23054;-0.01935;-1.16023;,
 -6.23054;-0.87686;-0.82567;,
 -6.23054;-1.13974;-0.45509;,
 -6.23054;-1.23204;-0.01798;,
 -6.23054;-1.13974;0.41914;,
 -6.23054;-0.87686;0.78973;,
 -6.23054;-0.48343;1.03733;,
 -6.23054;-0.01935;1.12428;,
 -6.23054;0.44473;1.03734;,
 -6.23054;0.83817;0.78973;,
 -6.23054;1.10105;0.41914;,
 -6.23054;1.19338;-0.01798;,
 -6.23054;1.10105;-0.45509;,
 -6.23054;0.83817;-0.82567;,
 -6.23054;0.44473;-1.07328;,
 -7.55914;-0.43292;-0.95842;,
 -7.55914;-0.01935;-1.03591;,
 -7.55914;-0.78352;-0.73776;,
 -7.55914;-1.01780;-0.40753;,
 -7.55914;-1.10006;-0.01798;,
 -7.55914;-1.01780;0.37157;,
 -7.55914;-0.78352;0.70182;,
 -7.55914;-0.43292;0.92247;,
 -7.55914;-0.01935;0.99996;,
 -7.55914;0.39422;0.92247;,
 -7.55915;0.74484;0.70182;,
 -7.55913;0.97911;0.37157;,
 -7.55914;1.06135;-0.01798;,
 -7.55913;0.97911;-0.40753;,
 -7.55915;0.74484;-0.73776;,
 -7.55914;0.39422;-0.95842;,
 -7.87017;-0.40572;-0.89658;,
 -7.87017;-0.01935;-0.96898;,
 -7.87017;-0.73328;-0.69043;,
 -7.87018;-0.95214;-0.38190;,
 -7.87017;-1.02901;-0.01798;,
 -7.87018;-0.95214;0.34596;,
 -7.87017;-0.73328;0.65448;,
 -7.87018;-0.40573;0.86064;,
 -7.87017;-0.01935;0.93303;,
 -7.87017;0.36703;0.86064;,
 -7.87017;0.69458;0.65448;,
 -7.87017;0.91345;0.34596;,
 -7.87017;0.99031;-0.01798;,
 -7.87017;0.91345;-0.38190;,
 -7.87017;0.69458;-0.69043;,
 -7.87017;0.36703;-0.89658;,
 -8.20704;-0.01935;-0.01798;;
 
 160;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,11,10;,
 3;0,12,11;,
 3;0,13,12;,
 3;0,14,13;,
 3;0,15,14;,
 3;0,16,15;,
 3;0,2,16;,
 4;2,1,17,18;,
 4;1,3,19,17;,
 4;3,4,20,19;,
 4;4,5,21,20;,
 4;5,6,22,21;,
 4;6,7,23,22;,
 4;7,8,24,23;,
 4;8,9,25,24;,
 4;9,10,26,25;,
 4;10,11,27,26;,
 4;11,12,28,27;,
 4;12,13,29,28;,
 4;13,14,30,29;,
 4;14,15,31,30;,
 4;15,16,32,31;,
 4;16,2,18,32;,
 4;18,17,33,34;,
 4;17,19,35,33;,
 4;19,20,36,35;,
 4;20,21,37,36;,
 4;21,22,38,37;,
 4;22,23,39,38;,
 4;23,24,40,39;,
 4;24,25,41,40;,
 4;25,26,42,41;,
 4;26,27,43,42;,
 4;27,28,44,43;,
 4;28,29,45,44;,
 4;29,30,46,45;,
 4;30,31,47,46;,
 4;31,32,48,47;,
 4;32,18,34,48;,
 4;34,33,49,50;,
 4;33,35,51,49;,
 4;35,36,52,51;,
 4;36,37,53,52;,
 4;37,38,54,53;,
 4;38,39,55,54;,
 4;39,40,56,55;,
 4;40,41,57,56;,
 4;41,42,58,57;,
 4;42,43,59,58;,
 4;43,44,60,59;,
 4;44,45,61,60;,
 4;45,46,62,61;,
 4;46,47,63,62;,
 4;47,48,64,63;,
 4;48,34,50,64;,
 4;50,49,65,66;,
 4;49,51,67,65;,
 4;51,52,68,67;,
 4;52,53,69,68;,
 4;53,54,70,69;,
 4;54,55,71,70;,
 4;55,56,72,71;,
 4;56,57,73,72;,
 4;57,58,74,73;,
 4;58,59,75,74;,
 4;59,60,76,75;,
 4;60,61,77,76;,
 4;61,62,78,77;,
 4;62,63,79,78;,
 4;63,64,80,79;,
 4;64,50,66,80;,
 4;66,65,81,82;,
 4;65,67,83,81;,
 4;67,68,84,83;,
 4;68,69,85,84;,
 4;69,70,86,85;,
 4;70,71,87,86;,
 4;71,72,88,87;,
 4;72,73,89,88;,
 4;73,74,90,89;,
 4;74,75,91,90;,
 4;75,76,92,91;,
 4;76,77,93,92;,
 4;77,78,94,93;,
 4;78,79,95,94;,
 4;79,80,96,95;,
 4;80,66,82,96;,
 4;82,81,97,98;,
 4;81,83,99,97;,
 4;83,84,100,99;,
 4;84,85,101,100;,
 4;85,86,102,101;,
 4;86,87,103,102;,
 4;87,88,104,103;,
 4;88,89,105,104;,
 4;89,90,106,105;,
 4;90,91,107,106;,
 4;91,92,108,107;,
 4;92,93,109,108;,
 4;93,94,110,109;,
 4;94,95,111,110;,
 4;95,96,112,111;,
 4;96,82,98,112;,
 4;98,97,113,114;,
 4;97,99,115,113;,
 4;99,100,116,115;,
 4;100,101,117,116;,
 4;101,102,118,117;,
 4;102,103,119,118;,
 4;103,104,120,119;,
 4;104,105,121,120;,
 4;105,106,122,121;,
 4;106,107,123,122;,
 4;107,108,124,123;,
 4;108,109,125,124;,
 4;109,110,126,125;,
 4;110,111,127,126;,
 4;111,112,128,127;,
 4;112,98,114,128;,
 4;114,113,129,130;,
 4;113,115,131,129;,
 4;115,116,132,131;,
 4;116,117,133,132;,
 4;117,118,134,133;,
 4;118,119,135,134;,
 4;119,120,136,135;,
 4;120,121,137,136;,
 4;121,122,138,137;,
 4;122,123,139,138;,
 4;123,124,140,139;,
 4;124,125,141,140;,
 4;125,126,142,141;,
 4;126,127,143,142;,
 4;127,128,144,143;,
 4;128,114,130,144;,
 3;130,129,145;,
 3;129,131,145;,
 3;131,132,145;,
 3;132,133,145;,
 3;133,134,145;,
 3;134,135,145;,
 3;135,136,145;,
 3;136,137,145;,
 3;137,138,145;,
 3;138,139,145;,
 3;139,140,145;,
 3;140,141,145;,
 3;141,142,145;,
 3;142,143,145;,
 3;143,144,145;,
 3;144,130,145;;
 
 MeshMaterialList {
  2;
  160;
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
  1;;
  Material {
   0.244800;0.649600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.708800;0.664800;0.380000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  146;
  1.000000;-0.000001;-0.000001;,
  0.804235;0.000006;-0.594311;,
  0.805950;-0.215645;-0.551309;,
  0.810183;-0.402475;-0.426165;,
  0.814543;-0.531265;-0.232975;,
  0.816383;-0.577511;-0.000002;,
  0.814541;-0.531268;0.232975;,
  0.810178;-0.402485;0.426165;,
  0.805948;-0.215650;0.551309;,
  0.804235;0.000008;0.594312;,
  0.805955;0.215644;0.551302;,
  0.810186;0.402470;0.426164;,
  0.814544;0.531261;0.232979;,
  0.816391;0.577500;-0.000001;,
  0.814548;0.531256;-0.232977;,
  0.810191;0.402464;-0.426162;,
  0.805956;0.215642;-0.551302;,
  0.289048;0.000000;-0.957315;,
  0.291032;-0.348895;-0.890827;,
  0.295983;-0.656302;-0.694019;,
  0.301183;-0.873477;-0.382527;,
  0.303412;-0.952859;-0.000001;,
  0.301181;-0.873478;0.382525;,
  0.295973;-0.656307;0.694018;,
  0.291020;-0.348905;0.890827;,
  0.289044;-0.000001;0.957316;,
  0.291035;0.348899;0.890824;,
  0.295985;0.656310;0.694010;,
  0.301193;0.873471;0.382534;,
  0.303440;0.952850;-0.000001;,
  0.301198;0.873468;-0.382535;,
  0.295991;0.656306;-0.694011;,
  0.291039;0.348892;-0.890826;,
  0.018473;-0.000001;-0.999829;,
  0.018630;-0.364784;-0.930906;,
  0.019013;-0.687170;-0.726248;,
  0.019422;-0.915926;-0.400877;,
  0.019603;-0.999808;-0.000002;,
  0.019425;-0.915927;0.400875;,
  0.019013;-0.687166;0.726252;,
  0.018623;-0.364791;0.930903;,
  0.018468;-0.000008;0.999829;,
  0.018622;0.364787;0.930905;,
  0.019010;0.687176;0.726242;,
  0.019432;0.915917;0.400897;,
  0.019618;0.999808;-0.000002;,
  0.019429;0.915916;-0.400899;,
  0.019007;0.687176;-0.726243;,
  0.018623;0.364781;-0.930907;,
  -0.022075;0.000000;-0.999756;,
  -0.022259;-0.364757;-0.930837;,
  -0.022724;-0.687122;-0.726186;,
  -0.023219;-0.915854;-0.400839;,
  -0.023433;-0.999725;-0.000004;,
  -0.023219;-0.915854;0.400840;,
  -0.022724;-0.687113;0.726195;,
  -0.022259;-0.364762;0.930835;,
  -0.022074;-0.000012;0.999756;,
  -0.022259;0.364757;0.930837;,
  -0.022726;0.687121;0.726188;,
  -0.023222;0.915842;0.400868;,
  -0.023437;0.999725;-0.000004;,
  -0.023223;0.915842;-0.400867;,
  -0.022728;0.687123;-0.726186;,
  -0.022261;0.364753;-0.930838;,
  -0.044980;0.000000;-0.998988;,
  -0.045358;-0.364468;-0.930111;,
  -0.046307;-0.686560;-0.725597;,
  -0.047311;-0.915074;-0.400502;,
  -0.047744;-0.998860;-0.000004;,
  -0.047312;-0.915073;0.400504;,
  -0.046307;-0.686554;0.725603;,
  -0.045356;-0.364475;0.930108;,
  -0.044977;-0.000012;0.998988;,
  -0.045357;0.364472;0.930109;,
  -0.046308;0.686560;0.725597;,
  -0.047314;0.915062;0.400527;,
  -0.047749;0.998859;-0.000004;,
  -0.047313;0.915064;-0.400525;,
  -0.046307;0.686558;-0.725599;,
  -0.045358;0.364466;-0.930111;,
  -0.036851;-0.000001;-0.999321;,
  -0.037162;-0.364593;-0.930425;,
  -0.037941;-0.686801;-0.725854;,
  -0.038765;-0.915410;-0.400653;,
  -0.039121;-0.999234;-0.000003;,
  -0.038765;-0.915410;0.400653;,
  -0.037940;-0.686803;0.725853;,
  -0.037161;-0.364597;0.930424;,
  -0.036852;-0.000008;0.999321;,
  -0.037161;0.364596;0.930424;,
  -0.037938;0.686804;0.725852;,
  -0.038762;0.915401;0.400671;,
  -0.039118;0.999235;-0.000003;,
  -0.038761;0.915402;-0.400671;,
  -0.037939;0.686798;-0.725857;,
  -0.037161;0.364593;-0.930425;,
  -0.055572;-0.000000;-0.998455;,
  -0.056038;-0.364272;-0.929605;,
  -0.057208;-0.686164;-0.725194;,
  -0.058444;-0.914529;-0.400276;,
  -0.058978;-0.998259;-0.000002;,
  -0.058444;-0.914532;0.400269;,
  -0.057206;-0.686166;0.725192;,
  -0.056038;-0.364267;0.929607;,
  -0.055574;-0.000006;0.998455;,
  -0.056037;0.364262;0.929609;,
  -0.057204;0.686167;0.725192;,
  -0.058444;0.914528;0.400278;,
  -0.058982;0.998259;-0.000002;,
  -0.058444;0.914525;-0.400285;,
  -0.057205;0.686161;-0.725197;,
  -0.056038;0.364267;-0.929607;,
  -0.152059;-0.000001;-0.988371;,
  -0.153303;-0.360508;-0.920072;,
  -0.156425;-0.678791;-0.717478;,
  -0.159718;-0.904315;-0.395859;,
  -0.161132;-0.986933;-0.000002;,
  -0.159715;-0.904319;0.395851;,
  -0.156421;-0.678794;0.717475;,
  -0.153296;-0.360502;0.920075;,
  -0.152051;-0.000002;0.988373;,
  -0.153303;0.360493;0.920078;,
  -0.156433;0.678791;0.717476;,
  -0.159723;0.904322;0.395840;,
  -0.161136;0.986932;-0.000002;,
  -0.159726;0.904318;-0.395848;,
  -0.156434;0.678788;-0.717479;,
  -0.153305;0.360501;-0.920074;,
  -0.663303;-0.000001;-0.748351;,
  -0.665034;-0.272213;-0.695435;,
  -0.669330;-0.510314;-0.539979;,
  -0.673790;-0.676787;-0.296590;,
  -0.675685;-0.737190;-0.000003;,
  -0.673789;-0.676790;0.296588;,
  -0.669328;-0.510326;0.539970;,
  -0.665035;-0.272211;0.695435;,
  -0.663297;0.000008;0.748356;,
  -0.665036;0.272207;0.695436;,
  -0.669337;0.510316;0.539968;,
  -0.673790;0.676793;0.296577;,
  -0.675678;0.737197;-0.000003;,
  -0.673792;0.676790;-0.296579;,
  -0.669338;0.510314;-0.539969;,
  -0.665036;0.272210;-0.695434;,
  -1.000000;0.000002;-0.000003;;
  160;
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
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,1,16;,
  4;1,2,18,17;,
  4;2,3,19,18;,
  4;3,4,20,19;,
  4;4,5,21,20;,
  4;5,6,22,21;,
  4;6,7,23,22;,
  4;7,8,24,23;,
  4;8,9,25,24;,
  4;9,10,26,25;,
  4;10,11,27,26;,
  4;11,12,28,27;,
  4;12,13,29,28;,
  4;13,14,30,29;,
  4;14,15,31,30;,
  4;15,16,32,31;,
  4;16,1,17,32;,
  4;17,18,34,33;,
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,26,42,41;,
  4;26,27,43,42;,
  4;27,28,44,43;,
  4;28,29,45,44;,
  4;29,30,46,45;,
  4;30,31,47,46;,
  4;31,32,48,47;,
  4;32,17,33,48;,
  4;33,34,50,49;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,42,58,57;,
  4;42,43,59,58;,
  4;43,44,60,59;,
  4;44,45,61,60;,
  4;45,46,62,61;,
  4;46,47,63,62;,
  4;47,48,64,63;,
  4;48,33,49,64;,
  4;49,50,66,65;,
  4;50,51,67,66;,
  4;51,52,68,67;,
  4;52,53,69,68;,
  4;53,54,70,69;,
  4;54,55,71,70;,
  4;55,56,72,71;,
  4;56,57,73,72;,
  4;57,58,74,73;,
  4;58,59,75,74;,
  4;59,60,76,75;,
  4;60,61,77,76;,
  4;61,62,78,77;,
  4;62,63,79,78;,
  4;63,64,80,79;,
  4;64,49,65,80;,
  4;65,66,82,81;,
  4;66,67,83,82;,
  4;67,68,84,83;,
  4;68,69,85,84;,
  4;69,70,86,85;,
  4;70,71,87,86;,
  4;71,72,88,87;,
  4;72,73,89,88;,
  4;73,74,90,89;,
  4;74,75,91,90;,
  4;75,76,92,91;,
  4;76,77,93,92;,
  4;77,78,94,93;,
  4;78,79,95,94;,
  4;79,80,96,95;,
  4;80,65,81,96;,
  4;81,82,98,97;,
  4;82,83,99,98;,
  4;83,84,100,99;,
  4;84,85,101,100;,
  4;85,86,102,101;,
  4;86,87,103,102;,
  4;87,88,104,103;,
  4;88,89,105,104;,
  4;89,90,106,105;,
  4;90,91,107,106;,
  4;91,92,108,107;,
  4;92,93,109,108;,
  4;93,94,110,109;,
  4;94,95,111,110;,
  4;95,96,112,111;,
  4;96,81,97,112;,
  4;97,98,114,113;,
  4;98,99,115,114;,
  4;99,100,116,115;,
  4;100,101,117,116;,
  4;101,102,118,117;,
  4;102,103,119,118;,
  4;103,104,120,119;,
  4;104,105,121,120;,
  4;105,106,122,121;,
  4;106,107,123,122;,
  4;107,108,124,123;,
  4;108,109,125,124;,
  4;109,110,126,125;,
  4;110,111,127,126;,
  4;111,112,128,127;,
  4;112,97,113,128;,
  4;113,114,130,129;,
  4;114,115,131,130;,
  4;115,116,132,131;,
  4;116,117,133,132;,
  4;117,118,134,133;,
  4;118,119,135,134;,
  4;119,120,136,135;,
  4;120,121,137,136;,
  4;121,122,138,137;,
  4;122,123,139,138;,
  4;123,124,140,139;,
  4;124,125,141,140;,
  4;125,126,142,141;,
  4;126,127,143,142;,
  4;127,128,144,143;,
  4;128,113,129,144;,
  3;129,130,145;,
  3;130,131,145;,
  3;131,132,145;,
  3;132,133,145;,
  3;133,134,145;,
  3;134,135,145;,
  3;135,136,145;,
  3;136,137,145;,
  3;137,138,145;,
  3;138,139,145;,
  3;139,140,145;,
  3;140,141,145;,
  3;141,142,145;,
  3;142,143,145;,
  3;143,144,145;,
  3;144,129,145;;
 }
 MeshTextureCoords {
  146;
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
