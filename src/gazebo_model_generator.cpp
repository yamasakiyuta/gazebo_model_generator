#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <stdio.h>

using namespace std;

void sdf_generator(string collada, string model_name)
{
    // ファイル出力ストリームの初期化
	string output_sdf = "models/" + model_name + "/model.sdf";
    std::ofstream ofs(output_sdf.c_str());

    // ファイルに1行ずつ書き込み
    ofs << "<?xml version='1.0'?>" << std::endl;
    ofs << "<sdf version='1.4'>" << std::endl;
    ofs << "    <model name='"+ model_name +"'>" << std::endl;
    ofs << "    <static>true</static>" << std::endl;
    ofs << "		<link name='link'>" << std::endl;
    ofs << "			<pose>0 0 0 0 0 0</pose>" << std::endl;
    ofs << "				<collision name='collision'>" << std::endl;
    ofs << "					<geometry>" << std::endl;
    ofs << "						<mesh><uri>model://"+model_name+"/meshes/"+collada+"</uri></mesh>" << std::endl;
    ofs << "					</geometry>" << std::endl;
    ofs << "				</collision>" << std::endl;
    ofs << "				<visual name='visual1'>" << std::endl;
    ofs << "					<geometry>" << std::endl;
    ofs << "						<mesh><uri>model://"+model_name+"/meshes/"+collada+"</uri></mesh>" << std::endl;
    ofs << "					</geometry>" << std::endl;
    ofs << "					<material>" << std::endl;
    ofs << "                 	<script>" << std::endl;
    ofs << "                 		<uri>model://asphalt_plane/materials/scripts</uri>" << std::endl;
    ofs << "                 		<uri>model://asphalt_plane/materials/textures</uri>" << std::endl;
    ofs << "                 		<name>vrc/asphalt</name>" << std::endl;
    ofs << "                	</script>" << std::endl;
    ofs << "                	</material>" << std::endl;
    ofs << "				</visual>" << std::endl;
    ofs << "		</link>" << std::endl;
    ofs << "	</model>" << std::endl;
    ofs << "</sdf>" << std::endl;
}

void cfg_generator(string collada, string model_name)
{
    // ファイル出力ストリームの初期化
	string output_config = "models/" + model_name + "/model.config";
    std::ofstream ofs(output_config.c_str());

    // ファイルに1行ずつ書き込み
    ofs << "<?xml version='1.0'?>" << std::endl;
    ofs << "<model>" << std::endl;
    ofs << "  <name>" + model_name + "</name>" << std::endl;
    ofs << "  <version>1.0</version>" << std::endl;
    ofs << "  <sdf version='1.4'>model.sdf</sdf>" << std::endl;
    ofs << "  <author>" << std::endl;
    ofs << "    <name>My Name</name>" << std::endl;
    ofs << "    <email>me@my.email</email>" << std::endl;
    ofs << "  </author>" << std::endl;
    ofs << "  <description>" << std::endl;
    ofs << "    My awsome model." << std::endl;
    ofs << "  </description>" << std::endl;
    ofs << "</model>" << std::endl;
}

void world_generator(string model_name)
{
    // ファイル出力ストリームの初期化
	string output_world = "models/" + model_name + "/worlds/" + model_name + ".world";
    std::ofstream ofs(output_world.c_str());

    // ファイルに1行ずつ書き込み
    ofs << "<?xml version='1.0'?>" << std::endl;
    ofs << "<sdf version='1.4'>" << std::endl;
    ofs << "    <world name='default'>" << std::endl;
    ofs << "        <include>" << std::endl;
    ofs << "            <uri>model://sun</uri>" << std::endl;
    ofs << "        </include>" << std::endl;
    ofs << "        <include>" << std::endl;
    ofs << "            <uri>model://" + model_name + "</uri>" << std::endl;
    ofs << "            <pose>0 0 0 0 0 0</pose>" << std::endl;
    ofs << "        </include>" << std::endl;
    ofs << "    </world>" << std::endl;
    ofs << "</sdf>" << std::endl;
}

void launch_generator(string model_name)
{
    // ファイル出力ストリームの初期化
	string output_world = "models/" + model_name + "/launch/" + model_name + "_empty.launch";
    std::ofstream ofs(output_world.c_str());

    // ファイルに1行ずつ書き込み
    ofs << "<?xml version='1.0'?>" << std::endl;
    ofs << "<launch>" << std::endl;
    ofs << "    <arg name='paused' default='false'/>" << std::endl;
    ofs << "    <arg name='use_sim_time' default='true'/>" << std::endl;
    ofs << "    <arg name='gui' default='true'/>" << std::endl;
    ofs << "    <arg name='headless' default='false'/>" << std::endl;
    ofs << "    <arg name='debug' default='false'/>" << std::endl;
    ofs << " " << std::endl;
    ofs << "    <include file='$(find gazebo_ros)/launch/empty_world.launch'>" << std::endl;
    ofs << "        <arg name='world_name' value='$(find package_name)/worlds/" + model_name + ".launch'>" << std::endl;
    ofs << "        <arg name='debug' value='$(arg debug)" << std::endl;
    ofs << "        <arg name='gui' value='$(arg gui)" << std::endl;
    ofs << "        <arg name='paused' value='$(arg paused)" << std::endl;
    ofs << "        <arg name='use_sim_time' value='$(arg use_sim_time)" << std::endl;
    ofs << "        <arg name='headless' value='$(arg headless)" << std::endl;
    ofs << "    <include>" << std::endl;
}

void make_model_dir(string model_name)
{
    string dr = "models/" + model_name;
    string mesh_dr = "models/" + model_name + "/meshes";
    string world_dr = "models/" + model_name + "/worlds";
    string launch_dr = "models/" + model_name + "/launch";
    
	if(!mkdir("models",0755)){
	  printf("generating models\n");
    }
    if(!mkdir(dr.c_str(),0755)){
	  printf("generating %s\n", dr.c_str());
    }
    if(!mkdir(mesh_dr.c_str(),0755)){
	  printf("generating %s\n", mesh_dr.c_str());
    }
    if(!mkdir(world_dr.c_str(),0755)){
	  printf("generating %s\n", world_dr.c_str());
    }
    if(!mkdir(launch_dr.c_str(),0755)){
	  printf("generating %s\n", launch_dr.c_str());
    }
}

string get_filename(const string &path)
{
	//printf("path = %s\n", path.c_str());
	size_t pos1;

	pos1 = path.rfind('\\');
	if(pos1 != string::npos){
		return path.substr(pos1+1,path.size()-pos1-1);
	}

	pos1 = path.rfind('/');
	if(pos1 != string::npos){
		return path.substr(pos1+1,path.size()-pos1-1);
	}
}

void move_meshfile(string &oldpath, string &meshfile, string model_name)
{
	string newpath = "./models/" + model_name + "/meshes/" + meshfile;
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
    
	string fullpath = argv[1];
    string filename = get_filename(argv[1]); //gazeboのモデルに使用するメッシュ(.dae)
    string model_name = argv[2]; //gazeboモデルの名前
    //printf("output file : %s\n",output.c_str());
    
    make_model_dir(model_name);//modelフォルダ作成
    sdf_generator(filename, model_name);//sdfファイル作成
    cfg_generator(filename, model_name);//cfgファイル作成
    world_generator(model_name);//worldファイル作成
    launch_generator(model_name);//launchファイル作成
	move_meshfile(fullpath, filename, model_name);//daeファイル移動

    return 0;
}
