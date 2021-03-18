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
 59;
 -22.31009;17.11957;-38.64314;,
 -26.38904;-4.85897;-29.52766;,
 -41.21359;18.23542;-18.13050;,
 -27.45551;37.99031;-26.38209;,
 -2.10164;0.90986;-46.67398;,
 -7.10813;31.13264;-40.57254;,
 -1.11465;45.71111;-36.86103;,
 17.12376;30.41226;-56.92978;,
 20.10127;42.94973;2.27659;,
 34.45011;42.93713;-21.48276;,
 10.95391;44.70333;-17.39510;,
 10.89624;13.32919;-54.39479;,
 16.52646;-4.49677;-51.81951;,
 -2.10164;0.90986;-46.67398;,
 10.89624;13.32919;-54.39479;,
 39.83959;29.35658;8.07635;,
 49.66329;17.60660;-15.94214;,
 10.95391;44.70333;-17.39510;,
 21.57150;41.62000;-35.76730;,
 21.57150;41.62000;-35.76730;,
 49.37505;23.86199;-34.96354;,
 17.12376;30.41226;-56.92978;,
 -1.11465;45.71111;-36.86103;,
 40.77206;9.54265;-52.63307;,
 41.36025;-6.07128;-31.11196;,
 33.68533;30.30350;-40.06346;,
 28.82003;-5.55901;-41.68304;,
 41.15850;-1.38210;3.96879;,
 40.68917;-3.81716;-14.39217;,
 33.99291;12.12489;12.15966;,
 24.87456;22.76848;29.53910;,
 11.53379;-15.08317;27.22422;,
 17.72213;2.50180;31.05098;,
 -7.04877;2.77747;46.27711;,
 25.48610;-10.24353;6.66252;,
 -8.41693;-16.11694;32.42412;,
 -34.37649;0.72551;36.44736;,
 22.20707;33.21828;15.33004;,
 9.43851;50.02987;21.25586;,
 -33.94536;-16.86934;16.88320;,
 -43.44925;5.10626;19.32930;,
 -41.35562;-6.86922;-7.79325;,
 -44.00452;16.57408;-0.76188;,
 7.76060;13.92469;36.06930;,
 -1.60797;28.93546;46.52185;,
 -36.21042;54.09854;-4.37850;,
 -39.46533;32.55608;-11.46495;,
 -45.85736;31.55966;16.68863;,
 -21.15032;20.61511;46.28646;,
 -38.74783;26.58509;42.33523;,
 -12.99145;44.26153;41.67892;,
 -7.11894;56.44721;1.64801;,
 -7.42510;55.59786;25.60827;,
 -31.14951;54.13972;23.52099;,
 -10.97735;48.14327;-15.07543;,
 -10.97735;48.14327;-15.07543;,
 4.59629;40.67449;34.45649;,
 -35.60415;40.92657;33.51912;,
 -19.01213;55.60663;12.44664;;
 
 89;
 3;0,1,2;,
 3;0,2,3;,
 3;4,0,5;,
 3;5,6,7;,
 3;1,0,4;,
 3;0,3,5;,
 3;3,6,5;,
 3;8,9,10;,
 3;4,5,11;,
 3;5,7,11;,
 3;12,13,14;,
 3;15,16,9;,
 3;8,15,9;,
 3;6,17,18;,
 3;10,9,19;,
 3;9,16,20;,
 3;19,21,22;,
 3;14,21,23;,
 3;12,14,23;,
 3;23,20,24;,
 3;23,21,25;,
 3;21,19,25;,
 3;20,23,25;,
 3;24,20,16;,
 3;19,9,25;,
 3;9,20,25;,
 3;12,23,26;,
 3;23,24,26;,
 3;16,15,27;,
 3;24,16,28;,
 3;16,27,28;,
 3;27,15,29;,
 3;15,30,29;,
 3;31,32,33;,
 4;27,29,32,34;,
 3;31,34,32;,
 3;31,33,35;,
 3;33,36,35;,
 3;32,29,30;,
 3;30,15,37;,
 3;15,8,37;,
 3;8,38,37;,
 3;38,30,37;,
 3;35,36,39;,
 3;39,36,40;,
 3;41,39,40;,
 3;2,1,41;,
 3;41,40,42;,
 3;2,41,42;,
 3;32,30,43;,
 3;30,44,43;,
 3;44,33,43;,
 3;33,32,43;,
 3;45,3,46;,
 3;3,2,46;,
 3;47,46,42;,
 3;46,2,42;,
 3;33,44,48;,
 3;49,40,36;,
 3;48,49,36;,
 3;44,50,48;,
 3;50,49,48;,
 3;8,10,51;,
 3;38,51,52;,
 3;33,48,36;,
 3;53,50,52;,
 3;50,38,52;,
 3;51,38,8;,
 3;3,45,54;,
 3;45,51,54;,
 3;51,17,54;,
 3;10,22,55;,
 3;54,6,3;,
 3;44,30,56;,
 3;30,38,56;,
 3;38,50,56;,
 3;50,44,56;,
 3;49,50,57;,
 3;50,53,57;,
 3;45,46,47;,
 3;53,52,58;,
 3;52,51,58;,
 3;51,45,58;,
 3;45,53,58;,
 3;57,53,47;,
 3;47,53,45;,
 3;42,40,47;,
 3;49,57,47;,
 3;47,40,49;;
 
 MeshMaterialList {
  2;
  89;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.668000;0.589600;0.558400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\�f�ތn\\_35652-220.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  55;
  0.179698;0.971020;-0.157574;,
  -0.224750;0.807905;-0.544772;,
  0.519193;0.849929;-0.089767;,
  0.469155;0.868431;0.160377;,
  0.580250;0.734567;0.351740;,
  -0.435998;0.839096;0.325307;,
  -0.495002;0.820463;-0.286030;,
  -0.560193;0.509320;-0.653282;,
  -0.426343;-0.065101;-0.902216;,
  0.320163;0.236201;-0.917445;,
  0.747201;0.439490;0.498537;,
  0.707152;0.117701;0.697196;,
  -0.690376;0.118451;0.713687;,
  -0.969142;0.233555;0.078837;,
  -0.560707;0.074118;-0.824690;,
  0.870358;-0.445213;-0.210388;,
  0.840402;-0.230569;0.490472;,
  0.533073;-0.459357;0.710510;,
  -0.531894;-0.437426;0.725085;,
  -0.962853;-0.209003;-0.170971;,
  -0.690458;-0.206898;-0.693153;,
  -0.876663;0.053532;-0.478117;,
  0.051847;0.508949;-0.859234;,
  -0.468302;0.247895;-0.848081;,
  0.992899;0.002885;0.118923;,
  0.044795;-0.402749;-0.914214;,
  0.170134;0.976487;-0.132392;,
  -0.285325;-0.077832;-0.955265;,
  0.291481;0.889979;-0.350680;,
  0.889555;0.312548;-0.333177;,
  0.503569;0.660433;-0.556998;,
  0.412690;-0.725739;-0.550444;,
  0.707368;-0.395006;0.586175;,
  0.922290;-0.382154;0.057792;,
  0.739053;-0.217661;0.637514;,
  0.358961;0.140619;0.922699;,
  0.623599;-0.234491;0.745747;,
  0.208012;-0.286111;0.935346;,
  -0.751954;-0.536911;0.382482;,
  -0.127016;-0.639878;0.757907;,
  0.619756;0.678564;0.394276;,
  -0.957546;-0.224236;0.181175;,
  -0.993162;0.011339;-0.116193;,
  0.509197;-0.104593;0.854271;,
  -0.914491;0.236349;-0.328399;,
  -0.177330;-0.010941;0.984091;,
  0.020410;0.594768;0.803638;,
  0.107772;0.954416;0.278343;,
  -0.036698;0.924651;-0.379043;,
  0.497121;0.548729;0.672136;,
  -0.643288;0.544739;0.537996;,
  -0.072091;0.997068;0.025639;,
  0.179981;0.981792;-0.060757;,
  0.627462;-0.617578;-0.474225;,
  0.376937;0.778536;0.501797;;
  89;
  3;14,20,21;,
  3;14,21,7;,
  3;8,14,23;,
  3;23,1,22;,
  3;20,14,8;,
  3;14,7,23;,
  3;7,1,23;,
  3;3,2,26;,
  3;8,23,27;,
  3;23,22,27;,
  3;25,8,27;,
  3;10,24,2;,
  3;3,10,2;,
  3;52,26,28;,
  3;26,2,28;,
  3;2,24,29;,
  3;28,22,1;,
  3;27,22,9;,
  3;25,27,9;,
  3;53,29,15;,
  3;9,22,30;,
  3;22,28,30;,
  3;29,9,30;,
  3;15,29,24;,
  3;28,2,30;,
  3;2,29,30;,
  3;25,53,31;,
  3;53,15,31;,
  3;24,10,16;,
  3;15,24,33;,
  3;24,16,33;,
  3;16,10,34;,
  3;10,11,34;,
  3;17,36,37;,
  4;16,34,36,32;,
  3;17,32,36;,
  3;17,37,39;,
  3;37,18,39;,
  3;36,34,11;,
  3;54,10,40;,
  3;10,3,40;,
  3;3,4,40;,
  3;4,11,40;,
  3;39,18,38;,
  3;38,18,41;,
  3;19,38,41;,
  3;21,20,19;,
  3;19,41,42;,
  3;21,19,42;,
  3;36,11,43;,
  3;11,35,43;,
  3;35,37,43;,
  3;37,36,43;,
  3;6,7,44;,
  3;7,21,44;,
  3;13,44,42;,
  3;44,21,42;,
  3;37,35,45;,
  3;12,41,18;,
  3;45,12,18;,
  3;35,46,45;,
  3;46,12,45;,
  3;3,26,0;,
  3;4,0,47;,
  3;37,45,18;,
  3;5,46,47;,
  3;46,4,47;,
  3;0,4,3;,
  3;7,6,48;,
  3;6,0,48;,
  3;0,26,48;,
  3;26,1,48;,
  3;48,1,7;,
  3;35,11,49;,
  3;11,4,49;,
  3;4,46,49;,
  3;46,35,49;,
  3;12,46,50;,
  3;46,5,50;,
  3;6,44,13;,
  3;5,47,51;,
  3;47,0,51;,
  3;0,6,51;,
  3;6,5,51;,
  3;50,5,13;,
  3;13,5,6;,
  3;42,41,13;,
  3;12,50,13;,
  3;13,41,12;;
 }
 MeshTextureCoords {
  59;
  0.916668;0.383388;,
  0.883924;0.538862;,
  0.815960;0.377510;,
  0.871827;0.250361;,
  0.992838;0.493802;,
  0.972397;0.293985;,
  0.995189;0.216084;,
  1.046502;0.349485;,
  0.267949;0.140116;,
  0.161258;0.241095;,
  0.089442;0.137196;,
  1.031465;0.424942;,
  0.049135;0.526257;,
  -0.007162;0.493802;,
  0.031465;0.424942;,
  0.281833;0.300911;,
  0.200564;0.396376;,
  1.089442;0.137196;,
  1.086373;0.250568;,
  0.086373;0.250568;,
  0.151936;0.380419;,
  0.046502;0.349485;,
  -0.004811;0.216084;,
  0.104897;0.454685;,
  0.147358;0.537170;,
  0.111270;0.332954;,
  0.096279;0.534778;,
  0.265300;0.510635;,
  0.195891;0.528079;,
  0.304674;0.396864;,
  0.388610;0.330426;,
  0.436221;0.650156;,
  0.417458;0.477762;,
  0.524057;0.481136;,
  0.290695;0.618050;,
  0.540423;0.642740;,
  0.620348;0.495391;,
  0.346162;0.217157;,
  0.433491;0.138512;,
  0.676544;0.633262;,
  0.683381;0.465952;,
  0.779644;0.551503;,
  0.752755;0.385357;,
  0.466271;0.385126;,
  0.505499;0.322971;,
  0.769152;0.188825;,
  0.794997;0.286747;,
  0.694451;0.317269;,
  0.568216;0.377486;,
  0.617963;0.361916;,
  0.548090;0.247810;,
  0.713794;0.040978;,
  0.544915;0.142338;,
  0.647065;0.198833;,
  0.899832;0.117634;,
  -0.100168;0.117634;,
  0.478894;0.225101;,
  0.629799;0.278180;,
  0.657746;0.123487;;
 }
}
