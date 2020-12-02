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
 276;
 -0.21674;283.75352;-25.43444;,
 5.59946;282.25318;-32.20164;,
 -0.21674;281.79512;-34.26840;,
 -0.21674;283.75352;-25.43444;,
 8.69422;283.41338;-26.96845;,
 -0.21674;283.75352;-25.43444;,
 7.61943;284.73277;-21.01748;,
 -0.21674;283.75352;-25.43444;,
 2.87802;285.59371;-17.13324;,
 -0.21674;283.75352;-25.43444;,
 -3.31150;285.59371;-17.13324;,
 -0.21674;283.75352;-25.43444;,
 -8.05290;284.73277;-21.01748;,
 -0.21674;283.75352;-25.43444;,
 -9.12769;283.41338;-26.96845;,
 -0.21674;283.75352;-25.43444;,
 -6.03294;282.25318;-32.20164;,
 -0.21674;283.75352;-25.43444;,
 -0.21674;281.79512;-34.26840;,
 -0.21674;-5.61758;38.80032;,
 -0.21674;-8.15591;27.35071;,
 7.32162;-7.56212;30.02944;,
 -0.21674;-5.61758;38.80032;,
 11.33267;-6.05833;36.81212;,
 -0.21674;-5.61758;38.80032;,
 -11.76614;-6.05833;36.81212;,
 -7.75510;-7.56212;30.02944;,
 -0.21674;-5.61758;38.80032;,
 -0.21674;-8.15591;27.35071;,
 10.25647;-4.73733;42.77092;,
 6.25191;-4.80930;42.44644;,
 -0.21674;-5.61758;38.80032;,
 0.98346;-4.90391;42.01964;,
 -0.21674;-5.61758;38.80032;,
 6.25191;-4.80930;42.44644;,
 -1.34646;-4.94583;41.83063;,
 -0.21674;-5.61758;38.80032;,
 0.98346;-4.90391;42.01964;,
 -5.05929;-5.01250;41.52988;,
 -0.21674;-5.61758;38.80032;,
 -1.34646;-4.94583;41.83063;,
 -5.05929;-5.01250;41.52988;,
 -11.00106;-5.11921;41.04836;,
 -0.21674;-5.61758;38.80032;,
 6.74651;87.86882;3.13739;,
 -0.21674;86.95127;0.74151;,
 10.44899;89.54022;9.34039;,
 -7.18386;87.21759;3.27724;,
 -10.89154;88.54382;9.55995;,
 -0.21674;86.95127;0.74151;,
 9.51222;90.73651;14.51440;,
 9.90731;-0.31929;43.61160;,
 9.16202;91.18370;16.44864;,
 3.48783;92.03114;21.13979;,
 3.74239;13.14395;45.77800;,
 -3.92238;91.68599;21.21951;,
 -4.17130;14.57931;45.44656;,
 -9.60249;90.30891;16.64700;,
 -10.31106;3.38411;42.77192;,
 -10.37958;89.24483;12.37468;,
 -4.44082;275.74434;-66.62676;,
 4.78886;275.74434;-66.62676;,
 4.78886;272.37115;-65.87896;,
 -4.44082;272.37115;-65.87896;,
 4.78886;276.50186;-63.20964;,
 4.78886;286.74063;-17.02565;,
 4.78886;283.36739;-16.27785;,
 4.78886;273.12867;-62.46184;,
 4.78886;287.58243;-13.22848;,
 4.78886;292.48057;8.86539;,
 4.78886;289.10733;9.61324;,
 4.78886;284.20918;-12.48064;,
 4.78886;293.32061;12.65432;,
 -4.44082;293.32061;12.65432;,
 -4.44082;289.94732;13.40215;,
 4.78886;289.94732;13.40215;,
 -4.44082;292.48057;8.86539;,
 -4.44082;287.58243;-13.22848;,
 -4.44082;284.20918;-12.48064;,
 -4.44082;289.10733;9.61324;,
 -4.44082;286.74063;-17.02565;,
 -4.44082;276.50186;-63.20964;,
 -4.44082;273.12867;-62.46184;,
 -4.44082;283.36739;-16.27785;,
 -4.44082;293.32061;12.65432;,
 4.78886;293.32061;12.65432;,
 4.78886;292.48057;8.86539;,
 -4.44082;292.48057;8.86539;,
 4.78886;287.58243;-13.22848;,
 -4.44082;287.58243;-13.22848;,
 4.78886;286.74063;-17.02565;,
 -4.44082;286.74063;-17.02565;,
 4.78886;276.50186;-63.20964;,
 -4.44082;276.50186;-63.20964;,
 4.78886;275.74434;-66.62676;,
 -4.44082;275.74434;-66.62676;,
 -4.44082;289.10733;9.61324;,
 4.78886;289.10733;9.61324;,
 4.78886;289.94732;13.40215;,
 -4.44082;289.94732;13.40215;,
 -4.44082;284.20918;-12.48064;,
 4.78886;284.20918;-12.48064;,
 -4.44082;283.36739;-16.27785;,
 4.78886;283.36739;-16.27785;,
 -4.44082;273.12867;-62.46184;,
 4.78886;273.12867;-62.46184;,
 -4.44082;272.37115;-65.87896;,
 4.78886;272.37115;-65.87896;,
 37.61314;293.32061;12.65432;,
 37.61314;292.48057;8.86539;,
 37.61314;289.94732;13.40215;,
 37.61314;289.10733;9.61324;,
 -37.26502;292.48057;8.86539;,
 -37.26502;293.32061;12.65432;,
 -37.26502;289.10733;9.61324;,
 -37.26502;289.94732;13.40215;,
 -4.11418;286.74063;-17.02565;,
 -4.11418;287.58243;-13.22848;,
 -4.11418;283.36739;-16.27785;,
 -4.11418;284.20918;-12.48064;,
 50.34934;287.58243;-13.22848;,
 50.34934;286.74063;-17.02565;,
 50.34934;284.20918;-12.48064;,
 50.34934;283.36739;-16.27785;,
 -49.67462;286.74063;-17.02565;,
 -49.67462;287.58243;-13.22848;,
 -49.67462;283.36739;-16.27785;,
 -49.67462;284.20918;-12.48064;,
 38.59063;276.50186;-63.20964;,
 38.59063;275.74434;-66.62676;,
 4.78886;275.74434;-66.62676;,
 38.59063;273.12867;-62.46184;,
 38.59063;272.37115;-65.87896;,
 4.78886;272.37115;-65.87896;,
 -38.24246;275.74434;-66.62676;,
 -38.24246;276.50186;-63.20964;,
 -4.44082;275.74434;-66.62676;,
 -38.24246;272.37115;-65.87896;,
 -4.44082;272.37115;-65.87896;,
 -38.24246;273.12867;-62.46184;,
 0.65058;155.71867;-19.62741;,
 2.59942;156.81391;-19.88537;,
 2.59942;159.88419;-6.40668;,
 0.65058;158.78891;-6.14873;,
 2.59942;159.00447;-20.40125;,
 2.59942;162.07467;-6.92257;,
 0.65058;160.09967;-20.65921;,
 0.65058;163.16995;-7.18049;,
 -1.29822;159.00447;-20.40125;,
 -1.29822;162.07467;-6.92257;,
 -1.29822;156.81391;-19.88537;,
 -1.29822;159.88419;-6.40668;,
 0.65058;155.71867;-19.62741;,
 0.65058;158.78891;-6.14873;,
 0.65058;157.90915;-20.14332;,
 0.65058;157.90915;-20.14332;,
 0.65058;157.90915;-20.14332;,
 0.65058;157.90915;-20.14332;,
 0.65058;157.90915;-20.14332;,
 0.65058;157.90915;-20.14332;,
 0.65058;160.97943;-6.66460;,
 0.65058;160.97943;-6.66460;,
 0.65058;160.97943;-6.66460;,
 0.65058;160.97943;-6.66460;,
 0.65058;160.97943;-6.66460;,
 0.65058;160.97943;-6.66460;,
 -1.08406;134.68207;11.59588;,
 -1.08406;137.75231;25.07460;,
 -3.03290;138.84755;24.81664;,
 -3.03290;135.77731;11.33792;,
 -3.03290;141.03803;24.30076;,
 -3.03290;137.96779;10.82208;,
 -1.08406;142.13332;24.04280;,
 -1.08406;139.06308;10.56412;,
 0.86474;141.03803;24.30076;,
 0.86474;137.96779;10.82208;,
 0.86474;138.84755;24.81664;,
 0.86474;135.77731;11.33792;,
 -1.08406;137.75231;25.07460;,
 -1.08406;134.68207;11.59588;,
 -1.08406;136.87251;11.08000;,
 -1.08406;136.87251;11.08000;,
 -1.08406;136.87251;11.08000;,
 -1.08406;136.87251;11.08000;,
 -1.08406;136.87251;11.08000;,
 -1.08406;136.87251;11.08000;,
 -1.08406;139.94275;24.55871;,
 -1.08406;139.94275;24.55871;,
 -1.08406;139.94275;24.55871;,
 -1.08406;139.94275;24.55871;,
 -1.08406;139.94275;24.55871;,
 -1.08406;139.94275;24.55871;,
 -0.73466;97.64827;-11.14609;,
 -0.73466;100.71851;2.33259;,
 -2.68350;101.81378;2.07464;,
 -2.68350;98.74351;-11.40405;,
 -2.68350;104.00426;1.55875;,
 -2.68350;100.93402;-11.91992;,
 -0.73466;105.09955;1.30083;,
 -0.73466;102.02926;-12.17789;,
 1.21414;104.00426;1.55875;,
 1.21414;100.93402;-11.91992;,
 1.21414;101.81378;2.07464;,
 1.21414;98.74351;-11.40405;,
 -0.73466;100.71851;2.33259;,
 -0.73466;97.64827;-11.14609;,
 -0.73466;99.83878;-11.66200;,
 -0.73466;99.83878;-11.66200;,
 -0.73466;99.83878;-11.66200;,
 -0.73466;99.83878;-11.66200;,
 -0.73466;99.83878;-11.66200;,
 -0.73466;99.83878;-11.66200;,
 -0.73466;102.90902;1.81672;,
 -0.73466;102.90902;1.81672;,
 -0.73466;102.90902;1.81672;,
 -0.73466;102.90902;1.81672;,
 -0.73466;102.90902;1.81672;,
 -0.73466;102.90902;1.81672;,
 -10.31106;3.38411;42.77192;,
 -11.00106;-5.11921;41.04836;,
 -1.34646;-4.94583;41.83063;,
 -4.17130;14.57931;45.44656;,
 -1.08406;75.23943;24.69831;,
 -1.08406;78.30967;38.17700;,
 -3.03290;79.40491;37.91907;,
 -3.03290;76.33463;24.44039;,
 -3.03290;81.59542;37.40316;,
 -3.03290;78.52515;23.92452;,
 -1.08406;82.69066;37.14523;,
 -1.08406;79.62042;23.66655;,
 0.86474;81.59542;37.40316;,
 0.86474;78.52515;23.92452;,
 0.86474;79.40491;37.91907;,
 0.86474;76.33463;24.44039;,
 -1.08406;78.30967;38.17700;,
 -1.08406;75.23943;24.69831;,
 -1.08406;77.42991;24.18244;,
 -1.08406;77.42991;24.18244;,
 -1.08406;77.42991;24.18244;,
 -1.08406;77.42991;24.18244;,
 -1.08406;77.42991;24.18244;,
 -1.08406;77.42991;24.18244;,
 -1.08406;80.50018;37.66116;,
 -1.08406;80.50018;37.66116;,
 -1.08406;80.50018;37.66116;,
 -1.08406;80.50018;37.66116;,
 -1.08406;80.50018;37.66116;,
 -1.08406;80.50018;37.66116;,
 -60.13894;253.98013;-24.76789;,
 60.28343;253.98013;-24.76789;,
 60.28343;246.99307;-23.21892;,
 -60.13894;246.99307;-23.21892;,
 60.28343;253.98013;-24.76789;,
 60.28343;255.52901;-17.78077;,
 60.28343;248.54200;-16.23176;,
 60.28343;246.99307;-23.21892;,
 60.28343;255.52901;-17.78077;,
 -60.13894;255.52901;-17.78077;,
 -60.13894;248.54200;-16.23176;,
 60.28343;248.54200;-16.23176;,
 -60.13894;255.52901;-17.78077;,
 -60.13894;253.98013;-24.76789;,
 -60.13894;246.99307;-23.21892;,
 -60.13894;248.54200;-16.23176;,
 60.28343;253.98013;-24.76789;,
 -60.13894;253.98013;-24.76789;,
 -60.13894;246.99307;-23.21892;,
 60.28343;246.99307;-23.21892;,
 10.25647;-4.73733;42.77092;,
 9.90731;-0.31929;43.61160;,
 3.74239;13.14395;45.77800;,
 6.25191;-4.80930;42.44644;,
 -4.17130;14.57931;45.44656;,
 -1.34646;-4.94583;41.83063;,
 6.25191;-4.80930;42.44644;,
 3.74239;13.14395;45.77800;;
 
 172;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,21;,
 3;22,21,23;,
 3;24,25,26;,
 3;27,26,28;,
 4;29,30,31,23;,
 3;32,33,34;,
 3;35,36,37;,
 3;38,39,40;,
 4;41,42,25,43;,
 4;44,21,20,45;,
 4;44,45,2,1;,
 4;46,23,21,44;,
 4;46,44,1,4;,
 4;47,26,25,48;,
 4;47,48,14,16;,
 4;49,28,26,47;,
 4;49,47,16,18;,
 3;46,4,50;,
 4;46,50,51,29;,
 3;46,29,23;,
 3;52,51,50;,
 4;52,50,4,6;,
 4;52,6,8,53;,
 4;52,53,54,51;,
 4;53,8,10,55;,
 4;53,55,56,54;,
 4;55,10,12,57;,
 4;55,57,58,56;,
 4;57,12,14,59;,
 4;57,59,42,58;,
 3;59,14,48;,
 4;59,48,25,42;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;96,97,98,99;,
 4;100,101,97,96;,
 4;102,103,101,100;,
 4;104,105,103,102;,
 4;106,107,105,104;,
 4;108,109,69,85;,
 4;110,108,85,98;,
 4;111,110,98,70;,
 4;109,111,70,69;,
 4;109,108,110,111;,
 4;112,113,84,76;,
 4;114,112,76,79;,
 4;115,114,79,99;,
 4;113,115,99,84;,
 4;113,112,114,115;,
 4;116,117,77,80;,
 4;118,116,80,83;,
 4;119,118,83,78;,
 4;117,119,78,77;,
 4;120,121,65,68;,
 4;122,120,68,71;,
 4;123,122,71,66;,
 4;121,123,66,65;,
 4;121,120,122,123;,
 4;124,125,117,116;,
 4;126,124,116,118;,
 4;127,126,118,119;,
 4;125,127,119,117;,
 4;125,124,126,127;,
 4;128,129,130,64;,
 4;131,128,64,67;,
 4;132,131,67,133;,
 4;129,132,133,130;,
 4;129,128,131,132;,
 4;134,135,81,136;,
 4;137,134,136,138;,
 4;139,137,138,82;,
 4;135,139,82,81;,
 4;135,134,137,139;,
 4;140,141,142,143;,
 4;141,144,145,142;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 3;154,141,140;,
 3;155,144,141;,
 3;156,146,144;,
 3;157,148,146;,
 3;158,150,148;,
 3;159,152,150;,
 3;160,143,142;,
 3;161,142,145;,
 3;162,145,147;,
 3;163,147,149;,
 3;164,149,151;,
 3;165,151,153;,
 4;166,167,168,169;,
 4;169,168,170,171;,
 4;171,170,172,173;,
 4;173,172,174,175;,
 4;175,174,176,177;,
 4;177,176,178,179;,
 3;180,166,169;,
 3;181,169,171;,
 3;182,171,173;,
 3;183,173,175;,
 3;184,175,177;,
 3;185,177,179;,
 3;186,168,167;,
 3;187,170,168;,
 3;188,172,170;,
 3;189,174,172;,
 3;190,176,174;,
 3;191,178,176;,
 4;192,193,194,195;,
 4;195,194,196,197;,
 4;197,196,198,199;,
 4;199,198,200,201;,
 4;201,200,202,203;,
 4;203,202,204,205;,
 3;206,192,195;,
 3;207,195,197;,
 3;208,197,199;,
 3;209,199,201;,
 3;210,201,203;,
 3;211,203,205;,
 3;212,194,193;,
 3;213,196,194;,
 3;214,198,196;,
 3;215,200,198;,
 3;216,202,200;,
 3;217,204,202;,
 4;218,219,220,221;,
 4;222,223,224,225;,
 4;225,224,226,227;,
 4;227,226,228,229;,
 4;229,228,230,231;,
 4;231,230,232,233;,
 4;233,232,234,235;,
 3;236,222,225;,
 3;237,225,227;,
 3;238,227,229;,
 3;239,229,231;,
 3;240,231,233;,
 3;241,233,235;,
 3;242,224,223;,
 3;243,226,224;,
 3;244,228,226;,
 3;245,230,228;,
 3;246,232,230;,
 3;247,234,232;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;260,253,264,265;,
 4;266,267,254,263;,
 4;268,269,270,271;,
 4;272,273,274,275;;
 
 MeshMaterialList {
  1;
  172;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "C:\\Users\\student\\Pictures\\3Dgame\\concrete00.jpg";
   }
  }
 }
 MeshNormals {
  188;
  0.000000;0.976297;-0.216437;,
  0.000000;0.976297;-0.216435;,
  0.000013;0.976296;-0.216442;,
  0.000004;0.976294;-0.216450;,
  -0.000007;0.976297;-0.216435;,
  -0.000009;0.976300;-0.216420;,
  0.000009;0.976300;-0.216420;,
  0.000007;0.976297;-0.216435;,
  -0.000004;0.976294;-0.216450;,
  -0.000013;0.976296;-0.216442;,
  0.000000;-0.976296;0.216441;,
  -0.000002;-0.976295;0.216446;,
  0.000005;-0.976296;0.216442;,
  -0.000003;-0.976296;0.216440;,
  0.000002;-0.976295;0.216446;,
  0.000001;-0.976297;0.216437;,
  0.925262;0.115914;0.361184;,
  0.360953;0.277777;0.890254;,
  -0.354736;0.279412;0.892240;,
  -0.876311;0.146584;0.458903;,
  0.000005;-0.976298;0.216432;,
  0.000001;-0.976298;0.216432;,
  0.000003;-0.976298;0.216431;,
  0.000005;-0.976299;0.216427;,
  -0.000003;-0.976298;0.216429;,
  -0.000001;-0.976299;0.216427;,
  0.000335;-0.223382;-0.974731;,
  0.643089;-0.168903;-0.746933;,
  0.994580;-0.013703;-0.103065;,
  0.870599;0.124220;0.476054;,
  0.352139;0.230695;0.907071;,
  -0.348464;0.231539;0.908274;,
  -0.871428;0.124278;0.474518;,
  -0.984792;-0.031528;-0.170854;,
  -0.642761;-0.169148;-0.747159;,
  0.985171;0.047924;0.164745;,
  -0.985200;0.047993;0.164552;,
  0.643243;-0.204113;-0.737954;,
  0.001337;-0.269416;-0.963023;,
  -0.000668;-0.176844;-0.984239;,
  0.642085;-0.133463;-0.754926;,
  0.984862;-0.039430;-0.168797;,
  0.998495;-0.001235;-0.054829;,
  -0.641925;-0.204659;-0.738950;,
  -0.984784;-0.039635;-0.169202;,
  -0.998504;-0.001209;-0.054664;,
  -0.642744;-0.133424;-0.754373;,
  0.985471;0.055083;0.160664;,
  0.866088;0.101653;0.489448;,
  0.342475;0.183291;0.921475;,
  -0.341344;0.183408;0.921871;,
  -0.865854;0.101782;0.489833;,
  -0.985542;0.055395;0.160118;,
  0.000000;-0.216435;-0.976297;,
  0.000000;-0.216435;-0.976297;,
  1.000000;0.000000;0.000000;,
  0.000000;0.216439;0.976296;,
  0.000000;0.216439;0.976296;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.976293;-0.216453;,
  0.000000;-0.976296;0.216441;,
  0.000000;0.216439;0.976296;,
  0.000000;-0.976296;0.216441;,
  0.000000;-0.216443;-0.976295;,
  0.000000;-0.976297;0.216436;,
  0.000000;0.976297;-0.216434;,
  0.000000;0.216431;0.976298;,
  0.000000;0.976297;-0.216436;,
  0.000000;-0.976297;0.216434;,
  0.000000;0.216442;0.976295;,
  0.000000;0.976297;-0.216436;,
  0.000000;-0.976297;0.216434;,
  0.000000;-0.216431;-0.976298;,
  0.000000;0.976298;-0.216429;,
  0.000000;-0.976298;0.216429;,
  0.000000;0.216435;0.976297;,
  0.000000;0.976294;-0.216449;,
  0.000000;0.976296;-0.216438;,
  0.000000;0.976296;-0.216439;,
  0.000000;0.976297;-0.216438;,
  0.000000;0.976296;-0.216438;,
  0.000000;0.976298;-0.216433;,
  0.000000;0.976298;-0.216429;,
  0.000000;-0.976296;0.216441;,
  0.000000;-0.976296;0.216441;,
  0.000000;-0.976296;0.216441;,
  0.000000;-0.976296;0.216441;,
  0.000000;-0.976296;0.216438;,
  0.000000;-0.976297;0.216437;,
  0.000000;-0.976297;0.216437;,
  0.000000;-0.976297;0.216436;,
  0.000000;-0.976298;0.216433;,
  0.000000;-0.976298;0.216429;,
  0.000000;-0.216443;-0.976295;,
  0.000000;0.216439;0.976296;,
  0.000000;-0.216442;-0.976295;,
  0.000000;-0.216431;-0.976298;,
  0.000000;-0.216435;-0.976297;,
  0.000000;0.216435;0.976297;,
  -0.000000;-0.229240;-0.973370;,
  0.500013;-0.844389;0.192341;,
  1.000000;0.000000;0.000000;,
  0.500003;0.844395;-0.192340;,
  -0.500011;0.844390;-0.192339;,
  -1.000000;0.000000;0.000000;,
  -0.000000;0.229236;0.973371;,
  -0.500020;-0.844385;0.192340;,
  0.000007;-0.229243;-0.973369;,
  0.000000;-0.229255;-0.973366;,
  0.000015;-0.229233;-0.973372;,
  -0.000000;-0.229234;-0.973371;,
  -0.000015;-0.229233;-0.973372;,
  -0.000007;-0.229243;-0.973369;,
  -0.000000;0.229233;0.973372;,
  0.000009;0.229236;0.973371;,
  0.000012;0.229237;0.973371;,
  -0.000000;0.229236;0.973371;,
  -0.000012;0.229237;0.973371;,
  -0.000009;0.229236;0.973371;,
  0.000000;-0.229231;-0.973372;,
  -0.500005;-0.844394;0.192340;,
  -1.000000;0.000000;0.000000;,
  -0.500020;0.844385;-0.192338;,
  0.500028;0.844380;-0.192337;,
  1.000000;0.000000;0.000000;,
  0.000000;0.229243;0.973369;,
  0.500012;-0.844389;0.192339;,
  -0.000000;-0.229242;-0.973369;,
  0.000002;-0.229232;-0.973372;,
  -0.000006;-0.229226;-0.973373;,
  0.000000;-0.229230;-0.973372;,
  0.000006;-0.229226;-0.973373;,
  -0.000002;-0.229232;-0.973372;,
  -0.000006;0.229241;0.973370;,
  0.000000;0.229243;0.973369;,
  -0.000003;0.229243;0.973369;,
  0.000000;0.229246;0.973369;,
  0.000003;0.229243;0.973369;,
  0.000006;0.229241;0.973370;,
  0.000000;-0.229241;-0.973370;,
  -0.500011;-0.844390;0.192340;,
  -1.000000;0.000000;0.000000;,
  -0.500011;0.844390;-0.192340;,
  0.500019;0.844385;-0.192339;,
  1.000000;0.000000;0.000000;,
  0.000000;0.229236;0.973371;,
  -0.075828;-0.192168;0.978428;,
  0.500018;-0.844386;0.192339;,
  -0.000000;-0.229251;-0.973367;,
  -0.000003;-0.229243;-0.973369;,
  -0.000009;-0.229237;-0.973371;,
  0.000000;-0.229239;-0.973370;,
  0.000009;-0.229237;-0.973371;,
  0.000003;-0.229243;-0.973369;,
  -0.000009;0.229237;0.973371;,
  0.000000;0.229234;0.973371;,
  -0.000012;0.229237;0.973371;,
  0.000000;0.229234;0.973371;,
  0.000012;0.229237;0.973371;,
  0.000009;0.229237;0.973371;,
  0.000000;-0.229236;-0.973371;,
  -0.499996;-0.844398;0.192342;,
  -1.000000;0.000000;0.000000;,
  -0.500009;0.844391;-0.192341;,
  0.500017;0.844386;-0.192340;,
  1.000000;0.000000;0.000000;,
  0.000000;0.229242;0.973369;,
  0.500003;-0.844394;0.192341;,
  0.000000;-0.229238;-0.973370;,
  -0.000007;-0.229236;-0.973371;,
  -0.000008;-0.229235;-0.973371;,
  0.000000;-0.229236;-0.973371;,
  0.000008;-0.229235;-0.973371;,
  0.000007;-0.229236;-0.973371;,
  -0.000014;0.229234;0.973371;,
  0.000000;0.229218;0.973375;,
  -0.000022;0.229254;0.973367;,
  0.000000;0.229257;0.973366;,
  0.000022;0.229254;0.973367;,
  0.000014;0.229234;0.973371;,
  0.000000;-0.216435;-0.976297;,
  1.000000;0.000000;0.000000;,
  0.000000;0.216442;0.976295;,
  -0.075838;-0.192169;0.978427;,
  -0.075838;-0.192168;0.978427;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.976300;-0.216422;,
  0.000000;-0.976299;0.216428;;
  172;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,1,9;,
  3;15,10,11;,
  3;15,11,12;,
  3;15,13,14;,
  3;15,14,10;,
  4;20,21,15,12;,
  3;22,15,21;,
  3;23,15,22;,
  3;25,15,23;,
  4;25,24,13,15;,
  4;27,37,38,26;,
  4;27,26,39,40;,
  4;28,41,37,27;,
  4;28,27,40,42;,
  4;34,43,44,33;,
  4;34,33,45,46;,
  4;26,38,43,34;,
  4;26,34,46,39;,
  3;28,42,35;,
  4;28,35,16,47;,
  3;28,47,41;,
  3;29,16,35;,
  4;29,35,42,48;,
  4;29,48,49,30;,
  4;29,30,17,16;,
  4;30,49,50,31;,
  4;30,31,18,17;,
  4;31,50,51,32;,
  4;31,32,19,18;,
  4;32,51,45,36;,
  4;32,36,52,19;,
  3;36,45,33;,
  4;36,33,44,52;,
  4;53,54,54,53;,
  4;55,55,55,55;,
  4;55,55,55,55;,
  4;56,57,57,56;,
  4;58,58,58,58;,
  4;58,58,58,58;,
  4;59,59,76,76;,
  4;76,76,77,78;,
  4;78,77,79,80;,
  4;80,79,81,81;,
  4;81,81,82,82;,
  4;83,84,85,86;,
  4;87,88,84,83;,
  4;89,90,88,87;,
  4;91,91,90,89;,
  4;92,92,91,91;,
  4;59,59,76,59;,
  4;61,61,56,56;,
  4;60,60,85,84;,
  4;93,93,93,93;,
  4;55,55,55,55;,
  4;59,59,59,76;,
  4;63,63,63,63;,
  4;62,62,83,86;,
  4;94,94,57,57;,
  4;58,58,58,58;,
  4;64,64,64,64;,
  4;66,66,66,66;,
  4;65,65,65,65;,
  4;95,95,95,95;,
  4;67,67,79,77;,
  4;69,69,69,69;,
  4;68,68,88,90;,
  4;96,96,96,96;,
  4;55,55,55,55;,
  4;70,70,70,70;,
  4;72,72,72,72;,
  4;71,71,71,71;,
  4;69,69,69,69;,
  4;58,58,58,58;,
  4;73,73,82,81;,
  4;75,75,75,75;,
  4;74,74,91,92;,
  4;97,97,54,54;,
  4;55,55,55,55;,
  4;73,73,81,82;,
  4;53,53,53,53;,
  4;74,74,92,91;,
  4;98,98,98,98;,
  4;58,58,58,58;,
  4;100,100,100,100;,
  4;101,101,101,101;,
  4;102,102,102,102;,
  4;103,103,103,103;,
  4;104,104,104,104;,
  4;106,106,106,106;,
  3;99,107,108;,
  3;99,109,107;,
  3;99,110,109;,
  3;99,111,110;,
  3;99,112,111;,
  3;99,108,112;,
  3;105,113,114;,
  3;105,114,115;,
  3;105,115,116;,
  3;105,116,117;,
  3;105,117,118;,
  3;105,118,113;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;126,126,126,126;,
  3;119,127,128;,
  3;119,128,129;,
  3;119,129,130;,
  3;119,130,131;,
  3;119,131,132;,
  3;119,132,127;,
  3;125,133,134;,
  3;125,135,133;,
  3;125,136,135;,
  3;125,137,136;,
  3;125,138,137;,
  3;125,134,138;,
  4;140,140,140,140;,
  4;141,141,141,141;,
  4;142,142,142,142;,
  4;143,143,143,143;,
  4;144,144,144,144;,
  4;147,147,147,147;,
  3;139,148,149;,
  3;139,149,150;,
  3;139,150,151;,
  3;139,151,152;,
  3;139,152,153;,
  3;139,153,148;,
  3;145,154,155;,
  3;145,156,154;,
  3;145,157,156;,
  3;145,158,157;,
  3;145,159,158;,
  3;145,155,159;,
  4;146,146,146,146;,
  4;161,161,161,161;,
  4;162,162,162,162;,
  4;163,163,163,163;,
  4;164,164,164,164;,
  4;165,165,165,165;,
  4;167,167,167,167;,
  3;160,168,169;,
  3;160,169,170;,
  3;160,170,171;,
  3;160,171,172;,
  3;160,172,173;,
  3;160,173,168;,
  3;166,174,175;,
  3;166,176,174;,
  3;166,177,176;,
  3;166,178,177;,
  3;166,179,178;,
  3;166,175,179;,
  4;180,180,180,180;,
  4;181,181,181,181;,
  4;182,182,182,182;,
  4;185,185,185,185;,
  4;186,186,186,186;,
  4;187,187,187,187;,
  4;183,183,183,183;,
  4;184,184,184,184;;
 }
 MeshTextureCoords {
  276;
  0.055560;0.000000;,
  0.111110;0.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.222220;0.000000;,
  0.277780;0.000000;,
  0.333330;0.000000;,
  0.388890;0.000000;,
  0.444440;0.000000;,
  0.500000;0.000000;,
  0.555560;0.000000;,
  0.611110;0.000000;,
  0.666670;0.000000;,
  0.722220;0.000000;,
  0.777780;0.000000;,
  0.833330;0.000000;,
  0.888890;0.000000;,
  0.944440;0.000000;,
  1.000000;0.000000;,
  0.055560;1.000000;,
  0.000000;1.000000;,
  0.111110;1.000000;,
  0.166670;1.000000;,
  0.222220;1.000000;,
  0.833330;1.000000;,
  0.777780;1.000000;,
  0.888890;1.000000;,
  0.944440;1.000000;,
  1.000000;1.000000;,
  0.308060;1.000000;,
  0.313160;1.000000;,
  0.277780;1.000000;,
  0.405510;1.000000;,
  0.388890;1.000000;,
  0.353510;1.000000;,
  0.515650;1.000000;,
  0.500000;1.000000;,
  0.483380;1.000000;,
  0.637600;1.000000;,
  0.611110;1.000000;,
  0.595460;1.000000;,
  0.695730;1.000000;,
  0.716750;1.000000;,
  0.722220;1.000000;,
  0.111110;0.666040;,
  0.000000;0.667320;,
  0.222220;0.665070;,
  0.888890;0.668290;,
  0.777780;0.668510;,
  1.000000;0.667320;,
  0.297150;0.664910;,
  0.333330;0.986060;,
  0.333330;0.664850;,
  0.444440;0.665480;,
  0.444440;0.943300;,
  0.555560;0.666680;,
  0.555560;0.938330;,
  0.666670;0.667870;,
  0.666670;0.973250;,
  0.737000;0.668260;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.200000;0.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.200000;1.000000;,
  0.600000;0.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.600000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.200000;0.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.200000;1.000000;,
  0.600000;0.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.600000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.000000;0.200000;,
  1.000000;0.400000;,
  0.000000;0.400000;,
  1.000000;0.600000;,
  0.000000;0.600000;,
  1.000000;0.800000;,
  0.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.800000;,
  1.000000;0.800000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.600000;,
  1.000000;0.600000;,
  0.000000;0.400000;,
  1.000000;0.400000;,
  0.000000;0.200000;,
  1.000000;0.200000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.800000;0.000000;,
  1.000000;1.000000;,
  0.800000;1.000000;,
  0.200000;0.000000;,
  0.000000;0.000000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.600000;0.000000;,
  0.400000;0.000000;,
  0.600000;1.000000;,
  0.400000;1.000000;,
  0.600000;0.000000;,
  0.400000;0.000000;,
  0.600000;1.000000;,
  0.400000;1.000000;,
  0.600000;0.000000;,
  0.400000;0.000000;,
  0.600000;1.000000;,
  0.400000;1.000000;,
  0.200000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.800000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.800000;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166670;1.000000;,
  0.166670;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
