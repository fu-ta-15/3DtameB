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
 0.00028;-0.00182;0.00037;,
 -1.45132;-0.30159;-0.99546;,
 -1.72702;-0.30041;-0.33983;,
 -0.95439;-0.30225;-1.49887;,
 -0.31183;-0.30221;-1.77348;,
 0.37855;-0.30154;-1.77743;,
 1.01157;-0.30029;-1.51011;,
 1.49097;-0.29871;-1.01229;,
 1.74368;-0.29701;-0.35975;,
 1.73127;-0.29545;0.34828;,
 1.45558;-0.29424;1.00389;,
 0.95865;-0.29362;1.50732;,
 0.31609;-0.29362;1.78189;,
 -0.37430;-0.29429;1.78589;,
 -1.00732;-0.29557;1.51857;,
 -1.48673;-0.29711;1.02077;,
 -1.73942;-0.29883;0.36815;,
 -1.70681;-0.54170;-1.16905;,
 -2.03122;-0.54027;-0.39749;,
 -1.12200;-0.54245;-1.76148;,
 -0.36581;-0.54241;-2.08462;,
 0.44657;-0.54161;-2.08925;,
 1.19153;-0.54016;-1.77470;,
 1.75566;-0.53831;-1.18888;,
 2.05304;-0.53631;-0.42093;,
 2.03839;-0.53444;0.41224;,
 1.71401;-0.53303;1.18372;,
 1.12921;-0.53229;1.77619;,
 0.37308;-0.53231;2.09929;,
 -0.43933;-0.53312;2.10394;,
 -1.18430;-0.53456;1.78937;,
 -1.74844;-0.53642;1.20359;,
 -2.04579;-0.53844;0.43561;,
 -1.81107;-0.89014;-1.23768;,
 -2.15567;-0.88865;-0.41815;,
 -1.18989;-0.89093;-1.86695;,
 -0.38666;-0.89092;-2.21019;,
 0.47626;-0.89007;-2.21519;,
 1.26757;-0.88854;-1.88104;,
 1.86680;-0.88656;-1.25877;,
 2.18273;-0.88442;-0.44304;,
 2.16717;-0.88245;0.44195;,
 1.82256;-0.88096;1.26150;,
 1.20142;-0.88018;1.89078;,
 0.39820;-0.88020;2.23405;,
 -0.46475;-0.88104;2.23892;,
 -1.25605;-0.88258;1.90484;,
 -1.85529;-0.88458;1.28254;,
 -2.17118;-0.88671;0.46679;,
 -1.76867;-3.00408;-1.19918;,
 -2.10642;-3.00166;-0.39588;,
 -1.15969;-3.00540;-1.81607;,
 -0.37240;-3.00538;-2.15248;,
 0.47352;-3.00391;-2.15733;,
 1.24920;-3.00143;-1.82981;,
 1.83658;-2.99812;-1.21981;,
 2.14623;-2.99462;-0.42018;,
 2.13105;-2.99131;0.44730;,
 1.79325;-2.98889;1.25062;,
 1.18433;-2.98755;1.86750;,
 0.39697;-2.98763;2.20397;,
 -0.44888;-2.98904;2.20874;,
 -1.22459;-2.99156;1.88128;,
 -1.81198;-2.99485;1.27130;,
 -2.12163;-2.99840;0.47163;,
 -1.69244;-4.48780;-1.13743;,
 -2.01700;-4.48544;-0.36553;,
 -1.10735;-4.48908;-1.73015;,
 -0.35078;-4.48903;-2.05348;,
 0.46198;-4.48767;-2.05809;,
 1.20739;-4.48527;-1.74340;,
 1.77179;-4.48209;-1.15726;,
 2.06931;-4.47867;-0.38890;,
 2.05471;-4.47556;0.44463;,
 1.73013;-4.47319;1.21657;,
 1.14506;-4.47191;1.80928;,
 0.38851;-4.47200;2.13256;,
 -0.42433;-4.47333;2.13723;,
 -1.16968;-4.47579;1.82255;,
 -1.73408;-4.47889;1.23639;,
 -2.03164;-4.48235;0.46806;,
 -1.55467;-6.57813;-1.03332;,
 -1.85429;-6.57594;-0.32063;,
 -1.01442;-6.57928;-1.58060;,
 -0.31593;-6.57922;-1.87908;,
 0.43459;-6.57799;-1.88337;,
 1.12275;-6.57577;-1.59281;,
 1.64388;-6.57285;-1.05164;,
 1.91859;-6.56968;-0.34222;,
 1.90511;-6.56679;0.42742;,
 1.60543;-6.56463;1.14011;,
 1.06520;-6.56345;1.68740;,
 0.36667;-6.56352;1.98591;,
 -0.38378;-6.56476;1.99020;,
 -1.07200;-6.56700;1.69964;,
 -1.59310;-6.56991;1.15846;,
 -1.86782;-6.57305;0.44902;,
 -1.42690;-8.36509;-0.93613;,
 -1.70362;-8.36311;-0.27809;,
 -0.92810;-8.36618;-1.44145;,
 -0.28319;-8.36613;-1.71702;,
 0.40973;-8.36495;-1.72101;,
 1.04511;-8.36287;-1.45270;,
 1.52626;-8.36019;-0.95304;,
 1.77990;-8.35730;-0.29805;,
 1.76745;-8.35464;0.41259;,
 1.49077;-8.35264;1.07058;,
 0.99199;-8.35157;1.46282;,
 0.34705;-8.35161;1.73843;,
 -0.34588;-8.35273;1.74240;,
 -0.98127;-8.35482;1.47416;,
 -1.46242;-8.35753;1.08755;,
 -1.71607;-8.36042;0.43253;,
 -1.34618;-8.99548;-0.87751;,
 -1.60798;-8.99360;-0.25494;,
 -0.87426;-8.99650;-1.35557;,
 -0.26405;-8.99649;-1.61637;,
 0.39152;-8.99539;-1.62010;,
 0.99271;-8.99343;-1.36629;,
 1.44791;-8.99088;-0.89353;,
 1.68786;-8.98813;-0.27380;,
 1.67608;-8.98562;0.39852;,
 1.41433;-8.98371;1.02111;,
 0.94240;-8.98267;1.38613;,
 0.33221;-8.98273;1.64685;,
 -0.32336;-8.98383;1.65062;,
 -0.92453;-8.98580;1.39677;,
 -1.37979;-8.98832;1.03713;,
 -1.61976;-8.99112;0.41739;,
 -1.23475;-9.40834;-0.79874;,
 -1.47569;-9.40659;-0.22572;,
 -0.80041;-9.40926;-1.23873;,
 -0.23883;-9.40923;-1.47870;,
 0.36456;-9.40821;-1.48221;,
 0.91786;-9.40641;-1.24856;,
 1.33684;-9.40404;-0.81343;,
 1.55770;-9.40155;-0.24312;,
 1.54688;-9.39924;0.37571;,
 1.30593;-9.39747;0.94872;,
 0.87158;-9.39653;1.38875;,
 0.30999;-9.39657;1.62867;,
 -0.29338;-9.39761;1.63214;,
 -0.84671;-9.39937;1.39857;,
 -1.26568;-9.40175;0.96347;,
 -1.48654;-9.40425;0.39310;,
 0.03257;-9.89378;0.07779;;
 
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
   0.244706;0.649412;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.709020;0.665098;0.379608;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  150;
  -0.001070;0.999997;-0.002384;,
  -0.392199;0.915971;-0.084717;,
  -0.333931;0.915551;-0.224178;,
  -0.225055;0.916537;-0.330620;,
  -0.081341;0.918270;-0.387509;,
  0.075338;0.919740;-0.385229;,
  0.220102;0.920221;-0.323650;,
  0.329991;0.919666;-0.212888;,
  0.388463;0.918723;-0.071025;,
  0.387812;0.918264;0.079958;,
  0.329047;0.918825;0.217920;,
  0.220853;0.920280;0.322968;,
  0.078647;0.921892;0.379381;,
  -0.076639;0.922703;0.377816;,
  -0.220883;0.922084;0.317760;,
  -0.331454;0.920168;0.208397;,
  -0.391455;0.917756;0.066980;,
  -0.789984;0.589676;-0.167954;,
  -0.672517;0.587813;-0.449663;,
  -0.454516;0.589937;-0.667375;,
  -0.164170;0.594478;-0.787175;,
  0.155630;0.598873;-0.785576;,
  0.451515;0.601027;-0.659470;,
  0.673249;0.600707;-0.431146;,
  0.787825;0.599459;-0.141354;,
  0.783541;0.599310;0.163986;,
  0.665057;0.601486;0.442621;,
  0.448411;0.605621;0.657382;,
  0.161132;0.609766;0.776030;,
  -0.155640;0.611398;0.775866;,
  -0.450415;0.608889;0.652978;,
  -0.673700;0.602708;0.427635;,
  -0.791420;0.595296;0.138842;,
  -0.965716;0.160577;-0.203981;,
  -0.821207;0.158125;-0.548284;,
  -0.555764;0.158268;-0.816136;,
  -0.200894;0.160467;-0.966381;,
  0.192699;0.163595;-0.967525;,
  0.558010;0.166482;-0.812963;,
  0.830679;0.168698;-0.530578;,
  0.970060;0.170573;-0.172882;,
  0.963868;0.172657;0.202850;,
  0.819084;0.175239;0.546254;,
  0.554034;0.177976;0.813247;,
  0.199979;0.179834;0.963155;,
  -0.192727;0.179557;0.964684;,
  -0.557681;0.176489;0.811076;,
  -0.830834;0.171205;0.529531;,
  -0.971101;0.165320;0.172139;,
  -0.977572;-0.044022;-0.205947;,
  -0.830952;-0.046248;-0.554418;,
  -0.562254;-0.047752;-0.825585;,
  -0.203083;-0.048131;-0.977978;,
  0.195518;-0.047022;-0.979572;,
  0.565782;-0.044377;-0.823360;,
  0.842376;-0.040687;-0.537353;,
  0.983918;-0.036777;-0.174796;,
  0.977920;-0.033440;0.206285;,
  0.831346;-0.031246;0.554876;,
  0.562605;-0.030482;0.826164;,
  0.203260;-0.031143;0.978629;,
  -0.195445;-0.032977;0.980160;,
  -0.565723;-0.035576;0.823828;,
  -0.842278;-0.038487;0.537668;,
  -0.983688;-0.041370;0.175062;,
  -0.976023;-0.071691;-0.205520;,
  -0.829609;-0.073944;-0.553427;,
  -0.561309;-0.075717;-0.824135;,
  -0.202687;-0.076464;-0.976254;,
  0.195251;-0.075597;-0.977835;,
  0.564916;-0.072925;-0.821920;,
  0.841145;-0.068942;-0.536398;,
  0.982546;-0.064653;-0.174421;,
  0.976622;-0.061073;0.206106;,
  0.830272;-0.058890;0.554238;,
  0.561884;-0.058379;0.825153;,
  0.203045;-0.059400;0.977366;,
  -0.195091;-0.061493;0.978855;,
  -0.564842;-0.064087;0.822707;,
  -0.840958;-0.066732;0.536969;,
  -0.982145;-0.069264;0.174909;,
  -0.975115;-0.083705;-0.205290;,
  -0.828839;-0.085744;-0.552878;,
  -0.560773;-0.087525;-0.823331;,
  -0.202480;-0.088449;-0.975284;,
  0.195085;-0.087845;-0.976845;,
  0.564394;-0.085438;-0.821072;,
  0.840359;-0.081671;-0.535842;,
  0.981650;-0.077556;-0.174207;,
  0.975744;-0.074167;0.205969;,
  0.820459;-0.077765;0.566392;,
  0.547590;-0.091579;0.831720;,
  0.202400;-0.103588;0.973809;,
  -0.194287;-0.105688;0.975235;,
  -0.550221;-0.096984;0.829368;,
  -0.831168;-0.085105;0.549470;,
  -0.981211;-0.081692;0.174789;,
  -0.971422;-0.120682;-0.204388;,
  -0.825646;-0.122817;-0.550659;,
  -0.558555;-0.124979;-0.819998;,
  -0.201633;-0.126365;-0.971276;,
  0.194371;-0.126042;-0.972797;,
  0.562258;-0.123526;-0.817684;,
  0.837248;-0.119308;-0.533648;,
  0.978154;-0.114637;-0.173417;,
  0.972383;-0.110845;0.205391;,
  0.798766;-0.115079;0.590533;,
  0.518289;-0.127429;0.845659;,
  0.201512;-0.140863;0.969304;,
  -0.193268;-0.143342;0.970618;,
  -0.520310;-0.133500;0.843478;,
  -0.809316;-0.123320;0.574283;,
  -0.977493;-0.118887;0.174279;,
  -0.951550;-0.233717;-0.199822;,
  -0.808637;-0.235792;-0.538988;,
  -0.546793;-0.238864;-0.802472;,
  -0.197200;-0.241608;-0.950125;,
  0.190358;-0.242277;-0.951349;,
  0.550446;-0.239823;-0.799684;,
  0.820017;-0.234722;-0.521994;,
  0.958613;-0.228821;-0.169415;,
  0.953406;-0.224264;0.201799;,
  0.786281;-0.200366;0.584479;,
  0.516124;-0.137636;0.845383;,
  0.202387;-0.099662;0.974221;,
  -0.194240;-0.103015;0.975530;,
  -0.517779;-0.146204;0.842929;,
  -0.795513;-0.211080;0.567983;,
  -0.957321;-0.232922;0.171126;,
  -0.686170;-0.713390;-0.142285;,
  -0.582760;-0.714644;-0.386878;,
  -0.392828;-0.717329;-0.575435;,
  -0.140732;-0.720190;-0.679353;,
  0.137041;-0.721519;-0.678697;,
  0.395016;-0.720224;-0.570298;,
  0.589730;-0.716555;-0.372516;,
  0.691795;-0.712076;-0.119866;,
  0.689815;-0.708705;0.147957;,
  0.588139;-0.692623;0.417571;,
  0.529192;-0.133965;0.837860;,
  0.202989;-0.053823;0.977701;,
  -0.194993;-0.057823;0.979099;,
  -0.530804;-0.144587;0.835070;,
  -0.589422;-0.700353;0.402600;,
  -0.689107;-0.713760;0.125213;,
  0.001314;-0.999992;0.003850;,
  0.171011;-0.952537;0.251852;,
  0.062364;-0.953594;0.294565;,
  -0.056003;-0.954489;0.292942;,
  -0.165808;-0.954724;0.247002;;
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
  3;138,146,145;,
  3;146,147,145;,
  3;147,148,145;,
  3;148,149,145;,
  3;149,143,145;,
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
