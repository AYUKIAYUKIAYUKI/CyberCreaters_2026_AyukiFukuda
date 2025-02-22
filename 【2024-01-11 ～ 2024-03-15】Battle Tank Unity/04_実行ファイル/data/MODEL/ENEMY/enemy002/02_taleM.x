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
 44;
 0.00000;15.14627;4.76381;,
 3.95833;14.36480;2.77619;,
 0.00000;15.68025;1.39146;,
 0.00000;15.14627;4.76381;,
 2.79182;13.61832;5.37269;,
 3.95833;14.36480;2.77619;,
 0.00000;13.24431;6.67370;,
 -2.79182;13.61832;5.37269;,
 -3.95833;14.36480;2.77619;,
 -3.95833;14.36480;2.77619;,
 6.85602;13.28286;1.58841;,
 0.00000;14.58289;-1.09131;,
 4.83558;11.91989;6.32931;,
 6.85602;13.28286;1.58841;,
 0.00000;11.27209;8.58268;,
 -4.83558;11.91989;6.32931;,
 -6.85602;13.28286;1.58841;,
 -6.85602;13.28286;1.58841;,
 7.91665;8.74458;-0.18868;,
 0.00000;9.68084;-3.44534;,
 5.58364;7.15597;5.33714;,
 7.91665;8.74458;-0.18868;,
 0.00000;6.40792;7.93908;,
 -5.58364;7.15597;5.33714;,
 -7.91665;8.74458;-0.18868;,
 -7.91665;8.74458;-0.18868;,
 6.85602;3.95547;-1.09313;,
 0.00000;4.27709;-4.05413;,
 4.83558;2.59251;3.64778;,
 6.85602;3.95547;-1.09313;,
 0.00000;1.94468;5.90114;,
 -4.83558;2.59251;3.64778;,
 -6.85602;3.95547;-1.09313;,
 -6.85602;3.95547;-1.09313;,
 3.95833;0.19872;-0.88262;,
 0.00000;-0.18047;-2.75456;,
 2.79182;-0.54776;1.71388;,
 3.95833;0.19872;-0.88262;,
 0.00000;-0.92177;3.01486;,
 -2.79182;-0.54776;1.71388;,
 -3.95833;0.19872;-0.88262;,
 -3.95833;0.19872;-0.88262;,
 0.00000;-1.51904;0.38648;,
 0.00000;-1.51904;0.38648;;
 
 36;
 3;0,1,2;,
 3;3,4,5;,
 3;3,6,4;,
 3;3,7,6;,
 3;3,8,7;,
 3;0,2,9;,
 4;2,1,10,11;,
 4;5,4,12,13;,
 4;4,6,14,12;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;9,2,11,17;,
 4;11,10,18,19;,
 4;13,12,20,21;,
 4;12,14,22,20;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;17,11,19,25;,
 4;19,18,26,27;,
 4;21,20,28,29;,
 4;20,22,30,28;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;25,19,27,33;,
 4;27,26,34,35;,
 4;29,28,36,37;,
 4;28,30,38,36;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;33,27,35,41;,
 3;35,34,42;,
 3;37,36,43;,
 3;36,38,43;,
 3;38,39,43;,
 3;39,40,43;,
 3;41,35,42;;
 
 MeshMaterialList {
  4;
  36;
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  1,
  1,
  1,
  1,
  0;;
  Material {
   0.552000;0.476800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy002\\enemy_skin.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy002\\enemy_skin.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\enemy002\\enemy_eyes.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  42;
  0.000000;0.893745;0.448575;,
  0.000000;0.996985;-0.077597;,
  0.374680;0.909439;0.180378;,
  0.327669;0.758406;0.563430;,
  0.000000;0.702070;0.712108;,
  -0.327669;0.758406;0.563430;,
  -0.374680;0.909439;0.180378;,
  0.000000;0.757452;-0.652891;,
  0.427367;0.901364;0.070004;,
  0.589128;0.403774;0.699924;,
  0.000000;0.330588;0.943775;,
  -0.589128;0.403774;0.699925;,
  -0.427367;0.901364;0.070004;,
  0.000000;0.276298;-0.961072;,
  0.398363;0.253428;-0.881522;,
  0.728820;-0.189184;0.658051;,
  0.000000;-0.276299;0.961072;,
  -0.728820;-0.189184;0.658051;,
  -0.926006;-0.104305;0.362812;,
  0.000000;-0.108818;-0.994062;,
  0.403234;-0.099579;-0.909663;,
  0.679227;-0.511593;0.526235;,
  0.000000;-0.573282;0.819358;,
  -0.679227;-0.511593;0.526236;,
  -0.863158;-0.441807;0.244468;,
  0.000000;-0.686246;-0.727370;,
  0.381573;-0.778027;-0.499075;,
  0.475691;-0.842997;0.251145;,
  0.000000;-0.880112;0.474766;,
  -0.475691;-0.842997;0.251145;,
  -0.501846;-0.857904;-0.110232;,
  0.000000;-0.995518;-0.094569;,
  0.393144;0.405169;-0.825395;,
  0.913034;0.057463;0.403816;,
  0.926006;-0.104305;0.362812;,
  -0.913034;0.057463;0.403816;,
  -0.393144;0.405169;-0.825395;,
  -0.398363;0.253428;-0.881522;,
  0.863158;-0.441807;0.244468;,
  -0.403234;-0.099579;-0.909663;,
  0.779690;-0.603268;0.167780;,
  -0.397999;-0.290421;-0.870202;;
  36;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,6,12,11;,
  4;6,1,7,12;,
  4;7,32,14,13;,
  4;33,9,15,34;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,35,18,17;,
  4;36,7,13,37;,
  4;13,14,20,19;,
  4;34,15,21,38;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,18,24,23;,
  4;37,13,19,39;,
  4;19,20,26,25;,
  4;38,21,27,40;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,24,30,29;,
  4;39,19,25,41;,
  3;25,26,31;,
  3;26,27,31;,
  3;27,28,31;,
  3;28,29,31;,
  3;29,30,31;,
  3;30,25,31;;
 }
 MeshTextureCoords {
  44;
  0.466226;-3.782003;,
  0.062137;-3.636227;,
  0.472585;-3.719855;,
  -0.750688;-1.665625;,
  -0.778255;-1.570549;,
  -0.626448;-1.627204;,
  -0.855394;-1.542959;,
  -0.780976;-1.572566;,
  -0.630306;-1.630064;,
  0.877812;-3.641130;,
  -0.234181;-3.488928;,
  0.477267;-3.529028;,
  -0.826097;-1.463893;,
  -0.548970;-1.567379;,
  -0.959704;-1.416108;,
  -0.830810;-1.467387;,
  -0.555652;-1.572333;,
  1.178610;-3.497420;,
  -0.340110;-2.986409;,
  0.481706;-2.972233;,
  -0.743533;-1.184316;,
  -0.420536;-1.304942;,
  -0.897809;-1.129136;,
  -0.748975;-1.188351;,
  -0.428252;-1.310663;,
  1.291240;-2.996215;,
  -0.229125;-2.490318;,
  0.482854;-2.425667;,
  -0.621091;-0.920606;,
  -0.343963;-1.024092;,
  -0.754698;-0.872820;,
  -0.625804;-0.924100;,
  -0.350646;-1.029046;,
  1.183666;-2.498811;,
  0.069036;-2.133580;,
  0.480404;-2.035776;,
  -0.491575;-0.743423;,
  -0.339769;-0.800079;,
  -0.568713;-0.715834;,
  -0.494297;-0.745440;,
  -0.343627;-0.802939;,
  0.884711;-2.138483;,
  0.474481;-2.011782;,
  -0.409078;-0.692928;;
 }
}
