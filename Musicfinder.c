//<가장 유사한 음악 찾기 프로그램>
//  Music_Finder3
//
//  Created by 2020315756 곽인애.
//

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SINGER_LENGTH 20
#define MAX_TITLE_LENGTH 20
#define MAX_SONGS 50
#include <stdio.h>
#include <string.h>

typedef struct {                    //노래 구조체
    char singer[MAX_SINGER_LENGTH];
    char title[MAX_TITLE_LENGTH];
    double SHz;
    double EHz;
    char key[4];
    int octave;
    char dynamic[10][10];

} Song;
Song songs[MAX_SONGS]={             //노래 구조체 배열(노래 데이터 저장)
        {"NEW JEANS","Ditto", 329.63, 987.77, "A", 3, {"p","mp","mf","f","cresc.","decresc."}},
        {"TAE YEON","INVU", 185.00, 1480.0,"Bm",4,{"p","mp","mf","dim"} },
        {"IVE","LOVE DIVE",329.63,493.88,"C#m",2,{"mp","p"}},
        {"BTS","Butter",207.65,523.25,"Ab",3,{"mp","mf","f"}},
        {"EXO","Power",329.63,783.99,"C",3,{"mf"}},
        {"Wanna One","Beautiful",196.00,440.00,"C",2,{"p"}},
        {"IU","Good day",246.94,739.99,"E",3,{"mp","mf","accent","cresc."}},
        {"StayC","Teddy Bear",220.00,659.26,"G",3,{"mp","accent","cresc."}},
        {"Lee Hi","Breath",138.36,622.25,"Ab",3,{"mp","f"}},
        {"Girls' Generation","Gee",246.94,739.99,"C#m",3,{"mp","accent","cresc."}},
        {"Aespa","Next Level",261.63,698.46,"F#m",3,{"cresc."}},
        {"LE SSERAFIM","Fearless",220.00,587.33,"Am",3,{"p","mp","f"}},
        {"Seventeen","Home",277.18,987.77,"A",3,{"dim"}},
        {"AKMU","Give Love",261.63,523.25,"F",4,{"accent"}},
        {"BIG BANG","Haru Haru",311.13,466.16,"Dm",2,{"accent","cresc.,"}},
        {"2NE1","I don't care",246.94,659.26,"E",3,{"accent"}},
        {"Black Pink","Pink Venom",220.00,783.99,"Em",3,{"p"}},
        {"Twice","Feel Special",415.30,1046.5,"Ab",4,{"mp"}},
        {"Red velvet","Psyco",233.08,1568.0,"Eb",4,{"mf","mp","decrec."}},
        {"Shinee","Ring Ding Dong",293.67,659.26,"Fm",3,{"accent","cresc."}},
        {"NCT 127","Kick It",329.63,830.61,"F#m",3,{"p","f","mf"}},
        {"IZONE","Panorama",220.00,1318.5,"Am",4,{"mp","mf","cresc."}},
        {"T-ara","Day by Day",392.00,987.77,"F#m",3,{"p","mf","decresc."}},
        {"IOI","Downpour",349.23,1318.5,"A",4,{"mp","p","mf","cresc."}},
        {"Winner","Really Really",196.00,783.99,"D",3,{"accent","cresc."}},
        {"IKON","Love Scenario",392.00,987.77,"Em",3,{"mp","p","mf","f","ff","decresc."}},
        {"Itzy","Wannabe",277.18,1108.7,"F#m",4,{"mp","p","mf","f","sf","cresc."}},
        {"Suzy","I Love You Boy",261.63,1244.5,"Ab",4,{"mp","mf","cresc."}},
        {"Yerin Baek","Here I Am Again",349.23,1318.5,"A",4,{"mp","p","mf","ff","sf","sfz","cresc.","decresc."}},
        {"Crush","Beautiful",174.61,698.46,"Bb",3,{"mp","p","mf","cresc.","decresc."}}
        
};
int num_songs=30;


void search_song(){
    double shz;
    double ehz;
    char Key_tone[4];
    int Octave;
    char Dynamics[10][10];
    int dynamic_num;
    int count[MAX_SONGS]={0,};
    int max, max_index;
    printf("What kind of song do you find?\n");
    printf("\nRange of Hz of the song:(시작,끝): ");    
    scanf("%lf",&shz);scanf("%lf",&ehz);            //주파수 범위 입력
    printf("주파수 범위: %lfhz~%lfhz",shz,ehz);
    printf("\n\nKey tone of the song: ");
    scanf(" %s",Key_tone);                          //조(key) 입력
    printf("\nOctave of the song: ");
    scanf(" %d",&Octave);                           //옥타브 입력
    printf("\nDynamics of the song\n");
    printf("\nHow many dynamics will you find?: "); //검색해볼 셈여림 개수 입력
    scanf(" %d",&dynamic_num);
    printf("\nInput %d dynamics: ",dynamic_num);
    for(int i=0;i<dynamic_num;i++){
    scanf(" %s",Dynamics[i]);                       //셈여림 입력
    }
    
    for(int i=0;i<num_songs;i++){                   //검색한 내용과 구조체 배열 내용들 비교
        if(songs[i].SHz==shz)count[i]++;
        if(songs[i].EHz==ehz)count[i]++;
        if(strstr(songs[i].key,Key_tone)!=NULL)count[i]++;
        if(songs[i].octave==Octave)count[i]++;
       for(int j=0;j<dynamic_num;j++){
            if(strstr(songs[i].dynamic[j],Dynamics[j])!=NULL)count[i]++;
        }
    }
    max=count[0];
    max_index=0;
    for(int i=0;i<num_songs;i++){       //가장 유사한 점이 많은 곡 위치 찾기
        if(count[i]>max){
            max=count[i];
            max_index=i;
        }
    }

    printf("\n<The most similar song>\n");                  //가장 유사한 곡의 가수와 제목 출력
    printf("Singer: %s\t",songs[max_index].singer); 
    printf("Title: %s\n",songs[max_index].title);


}

int main(){
    int choice;
    while(1){
        printf("\n\n=====Finding Similar Song=====\n\n");
        printf("1. Do you want to find a song?\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch(choice){
            case 1:
                search_song();                     //1: 음악 검색 함수 실행

                break;
            case 2:                                //2: 종료

                return 0;
            default:                               //3. 잘못 누름
                printf("Invalid choice\n");
        }
    }

        return 0;
    
    }
