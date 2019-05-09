#include <vector>
#include <tuple>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "mazeModel.h"
#include "esUtil.h"

#define pi acos(-1)
constexpr float eps = 1e-3;
using namespace std; 

namespace mazeModel {

	vector<Point> poi;//点集
	vector<unsigned short> index;//下标
	vector<int> jjiao;//现在的点对于平面来说的角度
	void init()//初始化
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}

	float dis(Point x, Point y) {
		auto [x1,y1] = x;
		auto [x2,y2] = y;
		return hypot(x1-x2,y1-y2);
	}

	tuple<vector<Point>, vector<unsigned short> > free(int arc, vector<string> const &gen) {
//		init();
		poi.clear();
		index.clear();
		jjiao.clear();
		poi.emplace_back(-1, 0);
		poi.emplace_back(1, 0);
		index.push_back(0);
		index.push_back(1);
		jjiao.push_back(0);
		vector<vector<int> > suma;//记录生成式
		for (const auto &j : gen) {
			int q = 0;
			vector<int> a;
			for (char i : j) {
				if (i == '+')
					q += arc;
				else if (i == '-')
					q -= arc;
				else {
					a.push_back((q % 360 + 360) % 360);
					q = 0;
				}
			}
			suma.push_back(a);
		}

		int ff = 0;
		while (ff == 0)//判断精度是否够
		{
			vector<Point> newpoi;
			vector<unsigned short> newindex;
			vector<int> newjjiao;
			int tot = 0;
			for (int i = 0; i < poi.size() - 1; i++) {
				int cd = static_cast<int>(rand() % gen.size());
				int j;
				for (j = 0; j < newpoi.size(); j++) {
					if (dis(newpoi[j],poi[i]) < eps)
						break;
				}
				if (j == newpoi.size()) {
					newpoi.push_back(poi[i]);
					newjjiao.push_back((jjiao[i] + suma[cd][0]) % 360);
					newindex.push_back(tot++);
				} else {
					newindex.push_back(j);
					newjjiao.push_back((jjiao[i] + suma[cd][0]) % 360);
				}
				float l = dis(poi[i], poi[i + 1]);
				if (l < eps)
					ff = 1;
				for (j = 1; j < suma[cd].size(); j++) {
					int size = newjjiao[newjjiao.size() - 1] + suma[cd][j];
					size %= 360;

					auto [lx,ly] = newpoi.back();
					auto nx = lx+ l / 3.0 * cos(newjjiao.back() * pi / 180.0);
					auto ny = ly+l / 3.0 * sin(newjjiao.back() * pi / 180.0);
					Point p(nx,ny);
//					p.x = newpoi[newpoi.size() - 1].x + l / 3.0 * cos(newjjiao[newjjiao.size() - 1] * pi / 180.0);
//					p.y = newpoi[newpoi.size() - 1].y + l / 3.0 * sin(newjjiao[newjjiao.size() - 1] * pi / 180.0);
					int k;
					for (k = 0; k < newpoi.size(); k++) {
                        if (dis(newpoi[j], p) < eps)
                            break;
                    }
					if (k == newpoi.size()) {
						newpoi.push_back(p);
						newjjiao.push_back(size);
						newindex.push_back(tot++);
					} else {
						newindex.push_back(k);
						newjjiao.push_back(size);
					}
					if (tot > 65530)
						break;
					ALOGE("233");
				}
				if (tot > 65530)
					break;
			}
			if (tot <= 65530) {
				poi = newpoi;
				jjiao = newjjiao;
				index = newindex;
				poi.emplace_back(1, 0);
				jjiao.push_back(0);
				int i;
				for (i = 0; i < poi.size(); i++) {
					if (dis(poi[i],Point(1.f,0.f))<eps)
						break;
				}
				if (i == poi.size())
					index.push_back(tot++);
				else
					index.push_back(i);
			} else
				ff = 1;
		}
		tuple<vector<Point>, vector<unsigned short> > tp(std::move(poi), std::move(index));
		/*FILE *fp;
        fp=fopen("out.txt","w");
        for(int i=0;i<poi.size();i++)
        {
            fprintf(fp,"%f %f %d\n",poi[i].x,poi[i].y,index[i]);
        }*/
		return tp;
	}

	struct MazeFunc mazeGenerator {
		.getMaze = free,
		.init = init
	};
/*int main()
{
	vector<string>s;
	string c;
	while(cin>>c)
	{
		if(c=="0")
			break;
		s.push_back(c);
	}
	int arc;
	cin>>arc;
	free(arc,s);
}*/

}