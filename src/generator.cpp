#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

void sdf_generator(std::string output)
{
    // ファイル出力ストリームの初期化
    std::ofstream ofs(output.c_str());

    // ファイルに1行ずつ書き込み
    ofs << "<?xml version='1.0'?>" << std::endl;
    ofs <<"	<sdf version='1.4'>" << std::endl;
    ofs <<"	<model name='D_kan'>" << std::endl; //model name変更できるようにする
    ofs <<"	<static>true</static>" << std::endl;
    ofs <<"		<link name='link'>" << std::endl;
    ofs <<"			<pose>0 0 0 0 0 0</pose>" << std::endl;
    ofs <<"				<collision name='collision1'>" << std::endl;
    ofs <<"					<geometry>" << std::endl;
    ofs <<"						<mesh><uri>model://ikuta_flipped/meshes/D_kan_2_rda.dae</uri></mesh>" << std::endl;//.daeファイル変更可能にする
    ofs <<"					</geometry>" << std::endl;
    ofs <<"				</collision>" << std::endl;
    ofs <<"				<visual name='visual1'>" << std::endl;
    ofs <<"					<geometry>" << std::endl;
    ofs <<"						<mesh><uri>model://ikuta_flipped/meshes/D_kan_2_rda.dae</uri></mesh>" << std::endl;
    ofs <<"					</geometry>" << std::endl;
    ofs <<"				</visual>" << std::endl;
    ofs <<"				<collision name='collision2'>" << std::endl;
    ofs <<"					<geometry>" << std::endl;
    ofs <<"						<mesh><uri>model://ikuta_flipped/meshes/D_kan_2_rda_f.dae</uri></mesh>" << std::endl;
    ofs <<"					</geometry>" << std::endl;
    ofs <<"				</collision>" << std::endl;
    ofs <<"				<visual name='visual2'>" << std::endl;
    ofs <<"					<geometry>" << std::endl;
    ofs <<"						<mesh><uri>model://ikuta_flipped/meshes/D_kan_2_rda_f.dae</uri></mesh>" << std::endl;
    ofs <<"					</geometry>" << std::endl;
    ofs <<"				</visual>" << std::endl;
    ofs <<"		</link>" << std::endl;
    ofs <<"	</model>" << std::endl;
    ofs << "</sdf>" << std::endl;
}

void make_model_dir(std::string model_name)
{
    std::string dr = "models/" + model_name;
    if(!mkdir("models",0755)){
	  printf("generating models\n");
    }
    if(!mkdir(dr.c_str(),0755)){
	  printf("generating %s\n",dr.c_str());
    }
}

void input()
{
    // ファイル入力ストリームの初期化
    std::ifstream ifs("C:\\home\\himitsu.txt");

    std::string line;
    while (std::getline(ifs, line)) {
        // ファイルの中身を一行づつ表示
        std::cout << line << std::endl;
    }
}

int main(int argc, char* argv[])
{
    //if(argc>3 || argc<2){
    if(argc != 3){
	    printf("ERROR\nUsage: ./model_generator mesh.dae model_name\n");
	    return 0;
    }
    //else if(argc<3){
	    //printf("ofile\n");
	    //ofile = filename;
    //}
    //else ofile = argv[2];
    
    std::string collada = argv[1]; //gazeboのモデルに使用するメッシュ(.dae)
    std::string model_name = argv[2]; //gazeboモデルの名前
    std::string sdf = "model.sdf";
    std::string output = "models/" + model_name + "/" + sdf;
    printf("output file : %s\n",output.c_str());
    
    make_model_dir(model_name);//フォルダ作成
    sdf_generator(output);//ファイル作成

    return 0;
}