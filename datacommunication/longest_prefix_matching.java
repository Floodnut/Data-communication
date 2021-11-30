import java.io.*;
import java.util.*;

class Main {
	
	public static void main(String[] args) throws Exception {

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<int[]> list = new ArrayList<>();
		int interfaceCnt = 0;
		char mode;
		String splitA;
		String ip;
		String[] Subnet;
		String subnetP;
		boolean isInput = true;
		Scanner sc = new Scanner(System.in);
		Main m = new Main();
		
		while(isInput){
			
			//입력
			String input = br.readLine();

			//입력 구분
			mode = input.charAt(0);
			
			splitA = input.substring(2).trim();
			
			//모드 확인
			if(Character.compare(mode, "I".charAt(0)) == 0 || Character.compare(mode, "i".charAt(0)) == 0){ //Input

				ip = splitA.split("/")[0];
				Subnet = ip.split("\\.");
				subnetP = (input.split(" ")[1].split("/"))[1].trim();;
				list = m.Input(list, Subnet, subnetP);
				interfaceCnt += 1;
			}
			if(Character.compare(mode, "S".charAt(0)) == 0 || Character.compare(mode, "s".charAt(0)) == 0){ //Search

				ip = splitA.trim();
				Subnet = ip.split("\\.");
				int result = m.Search(list, interfaceCnt, Subnet);
				
				if(interfaceCnt <= 0){
					System.out.println(interfaceCnt);
				}
				else if(result == -1){
					System.out.println(interfaceCnt);
				}
				else{
					System.out.println(Integer.toString(result));
				}
				break;
			}

		}
		return;

	}
	
	public ArrayList<int[]> Input(ArrayList<int[]> list, String[] i, String portion){
		int[] bit = new int[33];
		Arrays.fill(bit, 0);
		
		bit[32] = Integer.parseInt(portion);
		
		for(int j = 0 ; j < 4 ; j++){
			//bit[j] = String.valueOf(i[j]);
			bit[8*j + 0] = ((Integer.parseInt(i[j])) >> 7) & 1;
			bit[8*j + 1] = ((Integer.parseInt(i[j])) >> 6) & 1;
			bit[8*j + 2] = ((Integer.parseInt(i[j])) >> 5) & 1;
			bit[8*j + 3] = ((Integer.parseInt(i[j])) >> 4) & 1;
			bit[8*j + 4] = ((Integer.parseInt(i[j])) >> 3) & 1;
			bit[8*j + 5] = ((Integer.parseInt(i[j])) >> 2) & 1;
			bit[8*j + 6] = ((Integer.parseInt(i[j])) >> 1) & 1;
			bit[8*j + 7] = ((Integer.parseInt(i[j])) >> 0) & 1;
		}
		
		list.add(bit);
		return list;
	};
	
	public int Search(ArrayList<int[]> list,int listCount ,String[] i){
		int[] subnet = new int[32];
		int maxCount;
		int maxIndex = -1;
		int nowCount = 0;
		//int nowIndex = 0;
		for (int j = 0; j < 4 ; j++){
			subnet[8*j + 0] = ((Integer.parseInt(i[j])) >> 7) & 1;
			subnet[8*j + 1] = ((Integer.parseInt(i[j])) >> 6) & 1;
			subnet[8*j + 2] = ((Integer.parseInt(i[j])) >> 5) & 1;
			subnet[8*j + 3] = ((Integer.parseInt(i[j])) >> 4) & 1;
			subnet[8*j + 4] = ((Integer.parseInt(i[j])) >> 3) & 1;
			subnet[8*j + 5] = ((Integer.parseInt(i[j])) >> 2) & 1;
			subnet[8*j + 6] = ((Integer.parseInt(i[j])) >> 1) & 1;
			subnet[8*j + 7] = ((Integer.parseInt(i[j])) >> 0) & 1;
		}
        maxCount = 0;
		for(int j = 0 ; j < listCount ; j++){

			nowCount = 0;
			for(int k = 0 ; k < list.get(j)[32] ; k ++){
				if(list.get(j)[k] == subnet[k]){
					nowCount += 1;
                }
                else{
					if(nowCount == 0){
						break;
					}
					else if(nowCount > maxCount){
						maxCount = nowCount;
						maxIndex = j;
						break;
					}
					
				}
                if( k == (list.get(j)[32] - 1)){
					if(nowCount > maxCount){
						maxCount = nowCount;
						maxIndex = j;
                    }
				}
				
			}
		}
		
		return maxIndex;
	};
}
