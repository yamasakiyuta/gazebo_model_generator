#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <stdio.h>

void sdf_generator(std::string output,std::string collada,std::string model_name)
{
    // ファイル出力ストリームの初期化
    std::ofstream ofs(output.c_str());

    // ファイルに1行ずつ書き込み
    ofs << "<?xml version='1.0'?>" << std::endl;
    ofs <<"	<sdf version='1.4'>" << std::endl;
    ofs <<"	<model name='"+ model_name +"'>" << std::endl;
    ofs <<"	<static>true</static>" << std::endl;
    ofs <<"		<link name='link'>" << std::endl;
    ofs <<"			<pose>0 0 0 0 0 0</pose>" << std::endl;
    ofs <<"				<collision name='collision'>" << std::endl;
    ofs <<"					<geometry>" << std::endl;
    ofs <<"						<mesh><uri>model://"+model_name+"/meshes/"+collada+"</uri></mesh>" << std::endl;
    ofs <<"					</geometry>" << std::endl;
    ofs <<"				</collision>" << std::endl;
    ofs <<"				<visual name='visual1'>" << std::endl;
    ofs <<"					<geometry>" << std::endl;
    ofs <<"						<mesh><uri>model://"+model_name+"/meshes/"+collada+"</uri></mesh>" << std::endl;
    ofs <<"					</geometry>" << std::endl;
    ofs <<"    	         <material>" << std::endl;
    ofs <<"                <script>" << std::endl;
    ofs <<"                 <uri>model://asphalt_plane/materials/scripts</uri>" << std::endl;
    ofs <<"                 <uri>model://asphalt_plane/materials/textures</uri>" << std::endl;
    ofs <<"                 <name>vrc/asphalt</name>" << std::endl;
    ofs <<"               </script>" << std::endl;
    ofs <<"              </material>" << std::endl;
    ofs <<"				</visual>" << std::endl;
    ofs <<"		</link>" << std::endl;
    ofs <<"	</model>" << std::endl;
    ofs << "</sdf>" << std::endl;
}

void make_model_dir(std::string model_name)
{
    std::string dr = "models/" + model_name;
    std::string mesh_dr = "models/" + model_name + "/meshes";
    if(!mkdir("models",0755)){
	  printf("generating models\n");
    }
    if(!mkdir(dr.c_str(),0755)){
	  printf("generating %s\n",dr.c_str());
    }
    if(!mkdir(mesh_dr.c_str(),0755)){
	  printf("generating %s\n",mesh_dr.c_str());
    }
}

std::string get_filename(const std::string &path)
{
	//printf("path = %s\n", path.c_str());
	size_t pos1;

	pos1 = path.rfind('\\');
	if(pos1 != std::string::npos){
		return path.substr(pos1+1,path.size()-pos1-1);
	}

	pos1 = path.rfind('/');
	if(pos1 != std::string::npos){
		return path.substr(pos1+1,path.size()-pos1-1);
	}
}

void move_meshfile(std::string &oldpath, std::string &meshfile, std::string modelname)
{
	std::string newpath = "./models/" + modelname + "/meshes/" + meshfile;
		printf("%s => %s\n", oldpath.c_str(), newpath.c_str());
	if(rename(oldpath.c_str(), newpath.c_str()) == 0){
		printf("ファイル移動成功\n");
	}
	else printf("ファイル移動失敗\n");
}

int main(int argc, char* argv[])
{
    if(argc != 3){
	    printf("ERROR\nUsage: ./model_generator mesh.dae model_name\n");
	    return 0;
    }
    
	std::string fullpath = argv[1];
    std::string filename = get_filename(argv[1]); //gazeboのモデルに使用するメッシュ(.dae)
    std::string model_name = argv[2]; //gazeboモデルの名前
    std::string output = "models/" + model_name + "/model.sdf";
    printf("output file : %s\n",output.c_str());
    
    make_model_dir(model_name);//フォルダ作成
    sdf_generator(output, filename, model_name);//ファイル作成
	move_meshfile(fullpath, filename, model_name);//ファイル移動

    return 0;
}
