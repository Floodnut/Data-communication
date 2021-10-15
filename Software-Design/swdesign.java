/*
  Written by gsniper777, 2021
  
  
  Sample impl Code about other Team's Design

  Environment
  Eclipse + Java
  Presume MongoDB or JSON Supported DB env

  Additional Library
  JAVA Json-simple

  Duration : 2-Days
  06.02.2021 : Write
  06.03.2021 : Inspect and Modify
*/

package swDesign;

import java.util.ArrayList;
import java.util.Scanner;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import com.sun.tools.javac.code.Attribute.Array;

class MyFriendsList{ //external struct class
	public int nMyFriendID;
}

class PaymentInfo{//class 9
    public String strProductName;
    public String strProductImage;
    public int nProductPrice;
    public int nShoppingPoint;
}

class MyProductInfo{//class 9
    public String strReceiver;
    public String strSender;
    public int nPaymentCode;
    public int nExpiredDate;
    public boolean isUsed;
}

class ProductData{ //class 9
    public String strProductName;
    public String strProductImage;
    public String strProductBrand;
    public String strProductDescription;
    public int nProductCode;
    public int nProductPrice;
}

class DoPay{ //class 6
	protected int nTotalPrice;
	protected int nProductCode;
	
	protected int requestPay(int nTotalPrice, int nProductCode) {
		if(Success) {
			return nPaymentCode_FromExternalSystem;	
		}
		else {
			return 0;
		}
	}
	public DoPay(int nTotalPrice, int nProductCode) {
		this.nTotalPrice = nTotalPrice;
		this.nProductCode = nProductCode;
	}
}

class CreditCardPay extends DoPay{ //class 6
	public CreditCardPay(int nTotalPrice, int nProductCode) {
		super(nTotalPrice, nProductCode);
		// TODO Auto-generated constructor stub
	}
	protected int requestPay(int nTotalPrice, int nProductCode) { //U6.SeqDiagram : 7, error : private -> protected
		if(Success) {
			return nPaymentCode_FromExternalSystem; //U6.SeqDiagram : 8, 12
		}
		else {
			return 0; //U6.SeqDiagram : 8, 15
		}
	}
}
class MobilePay extends DoPay{ //class 6
	public MobilePay(int nTotalPrice, int nProductCode) {
		super(nTotalPrice, nProductCode);
		// TODO Auto-generated constructor stub
	}
	protected int requestPay(int nTotalPrice, int nProductCode) { //U6.SeqDiagram : 9, error : private -> protected
		if(Success) {
			return nPaymentCode_FromExternalSystem;//U6.SeqDiagram : 10, 13
		}
		else {
			return 0;	//U6.SeqDiagram : 10, 16
		}
	}
}
class KakaoPay extends DoPay{ //class 6
	public KakaoPay(int nTotalPrice, int nProductCode) {
		super(nTotalPrice, nProductCode);
		// TODO Auto-generated constructor stub
	}
	protected int requestPay(int nTotalPrice, int nProductCode) { //U6.SeqDiagram : 5, error : private -> protected
		boolean Success;
		if(Success) {
			return nPaymentCode_FromExternalSystem;//U6.SeqDiagram : 6, 11
		}
		else {
			return 0;	//U6.SeqDiagram : 6, 14
		}
	}
}

class DBConnect{ //class 2
    public String executeQuery(String query) { //U2.SeqDiagram : 1
        boolean bConnectResult = this.DBconnect();	//U2.SeqDiagram : 2
        
        if(bConnectResult == false) {	//U2.SeqDiagram : 3
        	return "ERROR";	//U2.SeqDiagram : 4
        }
        else {
        	String data = runQuery(query);	//U2.SeqDiagram : 5, 6
            this.DBclose();	//U2.SeqDiagram : 7
            return data;	//U2.SeqDiagram : 8
        }
    }
    private boolean DBconnect() { //U2.SeqDiagram : 2
        return bConnectResult;
    }
    private void DBclose() {};//U2.SeqDiagram : 7
    private String runQuery(String query) {//U2.SeqDiagram : 5
        return "__JSON_String__";
    }
}

class Exchange{ //class 7
    private String strCompleteMessage = "Complete"; 
    private String strCannotExchangeMessage = "CannotExchange";
    private String strRetriveRequestMessage = "RetriveRequest";
    private String strInquiry = "Inquiry"; //1
    private String strCheckExcValid = "__CheckExcValid_Query__";
    private String strData;
    private DBConnect dbConnect = new DBConnect();
	private boolean bRetrieveProduct = false; //add

    public void requestExchange(int nPaymentCode) { //U7.SeqDiagram : 2
        this.strData = dbConnect.executeQuery(this.strCheckExcValid); //U7.SeqDiagram : 3, 4

        if(this.strData == "false") { //false
            this.sendMessage(strCannotExchangeMessage); //U7.SeqDiagram : 5
        }
        else { //true
            if (this.oneonOneInquiry()==false) {	//U7.SeqDiagram : 6
                this.sendMessage(strCannotExchangeMessage);	//U7.SeqDiagram : 10
            }
            else {
                this.sendMessage(strRetriveRequestMessage);	//U7.SeqDiagram : 11
                this.sendProduct(nPaymentCode);	//U7.SeqDiagram : 12
                this.bRetrieveProduct = this.retrieveProduct(nPaymentCode);	//U7.SeqDiagram : 13, 14
                this.sendMessage(strCompleteMessage);//U7.SeqDiagram : 15
            }
        }
    }
    public boolean oneonOneInquiry() {	//U7.SeqDiagram : 6
        this.sendMessage(this.strInquiry);	//U7.SeqDiagram : 7
        try (Scanner input = new Scanner(System.in)) {
			String reply = input.nextLine();	//U7.SeqDiagram : 8
			return this.judge(reply);	//U7.SeqDiagram : 9
		}
    }
    public boolean judge(String judgeString) {	//U7.SeqDiagram : 9
        if(judgeString != null ) { //example condition
            return true;
        }
        else {
            return false;
        }
    }
    public void sendProduct(int nPaymentCode) { //U7.SeqDiagram : 12

    }
    public boolean retrieveProduct(int nPaymentCode) { //U7.SeqDiagram : 13
        if(__retrieveCondition__ == true) { //retrieve complete
            return true;
        }
        else { //retrieve fail
            return false;
        }
    }
    public void sendMessage(String message) {//U7.SeqDiagram : 5, 10, 11, 15
        System.out.println(message);
    }
}

class Refund{ //class 8
    private String strCompleteMessage = "Complete";
    private String strCannotRefundMessage = "CannotRefund";
    private String strRetriveRequestMessage = "RetriveRequest";
    private String strCheckRefValid = "__CheckExcValid_Query__";
    private String strData;
    private DBConnect dbConnect = new DBConnect();
	private boolean bRetrieveProduct = false; //add

    public void requestRefund(int nPaymentCode) {	//U8.SeqDiagram : 2
        this.strData = dbConnect.executeQuery(this.strCheckRefValid); //U8.SeqDiagram : 3, 4
        
		if(this.strData.contains("false")) { //U8.SeqDiagram : 5
            this.sendMessage(strCannotRefundMessage);//U8.SeqDiagram : 5
        }
        else {
            this.requestRefundToPaymentSystem(nPaymentCode);	//U8.SeqDiagram : 6, 7, error : 7 is void but it has return
            this.sendMessage(strRetriveRequestMessage);	//U8.SeqDiagram : 8
            this.bRetrieveProduct = this.retrieveProduct(nPaymentCode);	//U8.SeqDiagram : 9, 10
            this.sendMessage(strCompleteMessage);	//U8.SeqDiagram : 11
        }
    }
    public void requestRefundToPaymentSystem(int nPaymentCode) { //U8.SeqDiagram : 6, no return

    }
    public boolean retrieveProduct(int nPaymentCode) { //U8.SeqDiagram : 9
        if(__retrieveCondition__ == true) { //retrieve complete
            return true;	//U8.SeqDiagram : 10
        }
        else { //retrieve fail
            return false;	//U8.SeqDiagram : 10
        }
    }
    public void sendMessage(String message) {//U8.SeqDiagram : 11
        System.out.println(message);
    }
}

class Payment{ //class 5
	private Scanner scanner = new Scanner(System.in);
	private JSONParser jParse = new JSONParser();
	private DBConnect dbConnect = new DBConnect();
	private PaymentInfo paymentinfo = new PaymentInfo();
	private String strMessage;
	private String strData;
	private int nProductCode;
	private int nQuantity;
	private int nUsedPoint;
	private int nTotalPrice;
	private int nPaymentMethod; 
	private int nPaymentCode = 0;
	private int nReceiver;
	/*
	public int getPaymentCode() { //add : private 
		return nPaymentCode;
	}*/
	public void makePayment(int nProductCode) throws ParseException { //U5.SeqDiagram : 2, error : no return int_void
		MyFriendsList myFriendList; //external system struct
		this.strData = dbConnect.executeQuery("nProductCode_Query");	//U5.SeqDiagram : 3, 4

		if(!strData.contains("error")){ ////U5.SeqDiagram add : error check
			this.paymentinfo = this.dataParser(strData); //U5.SeqDiagram : 5
			
			this.nReceiver=this.selectFriend(myFriendsList); //U5.SeqDiagram : 6, external system object
			
			this.nQuantity = this.getQuantity();//U5.SeqDiagram : 7
			this.strMessage = this.getMessage();//U5.SeqDiagram : 8
			this.nUsedPoint = this.useShoppingPoint();//U5.SeqDiagram : 9
			this.nTotalPrice = this.calcTotalPrice(this.paymentinfo.nProductPrice, this.nQuantity, this.nUsedPoint);//U5.SeqDiagram : 10, modify : in useShoppingPoint -> out
			
			while(this.nPaymentCode == 0){//jump to U6.PaymentDiagram
				this.nPaymentMethod = this.getPaymentMethod(); //U6.SeqDiagram : 1

				if(this.nPaymentMethod==1){
					KakaoPay kakaoPay= new KakaoPay(this.nTotalPrice,this.nProductCode);//U6.SeqDiagram : 2
					this.nPaymentCode = kakaoPay.requestPay(kakaoPay.nTotalPrice, kakaoPay.nProductCode); //U6.SeqDiagram : 5
					kakaoPay = null;//U6.SeqDiagram : 17
				}
				else if(this.nPaymentMethod==2){
					CreditCardPay card = new CreditCardPay(this.nTotalPrice,this.nProductCode);//U6.SeqDiagram : 3
					this.nPaymentCode = card.requestPay(card.nTotalPrice, card.nProductCode); //U6.SeqDiagram : 7
					card = null;//U6.SeqDiagram : 18
				}
				else if(this.nPaymentMethod==3){
					MobilePay mobilePay = new MobilePay(this.nTotalPrice, this.nProductCode);//U6.SeqDiagram : 4
					this.nPaymentCode = mobilePay.requestPay(mobilePay.nTotalPrice, mobilePay.nProductCode); //U6.SeqDiagram : 9
					mobilePay = null;//U6.SeqDiagram : 19
				}
			}
			
			boolean result = this.sendResult(this.nPaymentCode, this.nReceiver,this.strMessage); //U5.SeqDiagram : 11, error : class diagram second Parameter String-Int Type
			if(result){
				System.out.println("success"); //U5.SeqDiagram : 14
			}
			else{
				this.cancelPay(this.nPaymentCode);	//U5.SeqDiagram : 15
				System.out.println("Fail");	//U5.SeqDiagram : 16
			}
		}
	}
	private int getQuantity(){//U5.SeqDiagram : 7
			System.out.print("Input Quantity :");
			return scanner.nextInt();
	}
	private String getMessage() {//U5.SeqDiagram : 8
			System.out.print("Input Message :");
			return scanner.nextLine();
	}
	private int getPaymentMethod() {
			System.out.print("Choose PaymentMethod :");
			return scanner.nextInt();
	}
	private int useShoppingPoint(){ //U5.SeqDiagram : 9
			System.out.print("Input ShoppingPoints:");
			return scanner.nextInt();
	}
	private int calcTotalPrice(int nProductPrice, int nQuantity, int nUsedPoint) { //U5.SeqDiagram : 10
		return ((nProductPrice*nQuantity)-nUsedPoint);
	}
	private boolean sendResult(int nPaymentCode,int nReceiver, String strMessage) throws ParseException { //U5.SeqDiagram : 11, second Parameter String-Int Type
		String queryPaymentCodeReceiverMessage = "query" + Integer.toString(nPaymentCode) + nReceiver + strMessage;
		JSONObject jObj = (JSONObject)this.jParse.parse(this.dbConnect.executeQuery(queryPaymentCodeReceiverMessage)); //U5.SeqDiagram : 12, 13

		return (Boolean)jObj.get("sendResult");
	}
	private void cancelPay(int nPaymentCode) {
	}
	private int selectFriend(MyFriendsList myFriendsList) {
		return myFriendsList.nMyFriendID;
	}	
	private PaymentInfo dataParser(String data) throws ParseException{ 
        PaymentInfo parsedData = new PaymentInfo();

        /*Parse from JSON String data*/
        try {
        	JSONObject jObj = (JSONObject)this.jParse.parse(data);
        	
	        parsedData.strProductName = (String)jObj.get("strProductName");
	        parsedData.strProductImage = (String)jObj.get("strProductImage");
	        parsedData.nProductPrice = (Integer)jObj.get("nProductPrice");
	        parsedData.nShoppingPoint = (Integer)jObj.get("nShoppingPoint");
	    } catch(ParseException e) { e.printStackTrace(); 	}

        return parsedData;
	}
}

/*
interface ShowDetail{ //class 4 interface
	public void showProductDetail();
}
*/
class ShowProductDetail{ //class 4
    private DBConnect dbConnect = new DBConnect();	//U4.SeqDiagram : 4
    public MyProductInfo myProductInfo = new MyProductInfo(); //error : no use
    public String strData; //add for getProductDetail

    public void showProductDetail(ProductData productData) {//U4.SeqDiagram : 10
    	//print or alert;
    }
    public void showProductError(String error) { //U4.SeqDiagram : 8, add : parameter type, no method
    	System.out.println(error);
    }
    public String getProductDetail(ProductData productData) { //U4.SeqDiagram : 3
    	String data = this.dbConnect.executeQuery("query");	//U4.SeqDiagram : 5, 6
    	this.dbConnect = null;	//U4.SeqDiagram : 7
    	return data;
    }
    public void requestPayment(ProductData productData) throws ParseException { //U4.SeqDiagram :13
    	Payment pay = new Payment();	 //U4.SeqDiagram :12
    	pay.makePayment(productData.nProductCode); //U5.PayDiagram, U5.SeqDiagram : 1
		pay = null;  //U4.SeqDiagram :14
    }
    public ProductData productParser(String data) throws ParseException {//U4.SeqDiagram : 9
    	ProductData parsedData = new ProductData();

        /*Parse from JSON String data1*/
    	JSONParser jParse = new JSONParser();
        JSONObject jObj = (JSONObject)jParse.parse(data);

        parsedData.strProductName = (String)jObj.get("strProductName");
        parsedData.strProductImage = (String)jObj.get("strProductImage");
        parsedData.strProductBrand = (String)jObj.get("strProductBrand");
        parsedData.strProductDescription = (String)jObj.get("strProductDescription");
        parsedData.nProductCode = (Integer)jObj.get("nProductCode");
        parsedData.nProductPrice = (Integer)jObj.get("nProductPrice");

        return parsedData;
    }
}

class ShowMyProductDetail { //class 4
    private DBConnect dbConnect = new DBConnect(); //U4.SeqDiagram :18
    public MyProductInfo myProductInfo = new MyProductInfo();
    public PaymentInfo paymentInfo = new PaymentInfo();
    private JSONParser jParse = new JSONParser();

    public String getPaymentInfo(MyProductInfo myProductInfo) {	//U4.SeqDiagram :21
        return dbConnect.executeQuery("query");	//U4.SeqDiagram :19, 20
    }
    public String getMyProductInfo(MyProductInfo myProductInfo) {	//U4.SeqDiagram :17
        return dbConnect.executeQuery("query");	//U4.SeqDiagram :22, 23
    }
    public MyProductInfo productParser(String data1) throws ParseException { //U4.SeqDiagram :25
        MyProductInfo parsedData1 = new MyProductInfo(); 

        /*Parse from JSON String data1*/
        JSONObject jObj = (JSONObject)this.jParse.parse(data1);

        parsedData1.strReceiver = (String)jObj.get("strReceiver");
        parsedData1.strSender = (String)jObj.get("strSender");
        parsedData1.nPaymentCode = (Integer)jObj.get("nPaymentCode");
        parsedData1.nExpiredDate = (Integer)jObj.get("nExpiredDate");
        parsedData1.isUsed = (Boolean)jObj.get("isUsed");

        return parsedData1;
    }
    public PaymentInfo paymentParser(String data2) { //U4.SeqDiagram :26
        PaymentInfo parsedData2 = new PaymentInfo();

        /*Parse from JSON String data2*/
        try {
        	JSONObject jObj = (JSONObject)this.jParse.parse(data2);
        	
	        parsedData2.strProductName = (String)jObj.get("strProductName");
	        parsedData2.strProductImage = (String)jObj.get("strProductImage");
	        parsedData2.nProductPrice = (Integer)jObj.get("nProductPrice");
	        parsedData2.nShoppingPoint = (Integer)jObj.get("nShoppingPoint");
	    } catch(ParseException e) { e.printStackTrace(); }

        return parsedData2;
    }
    public void showProductError(String strMyProductInfo, String strPayInfo) { //U4.SeqDiagram :24
        System.out.println(strMyProductInfo + strPayInfo); //print error
    }
    public void showProductDetail(MyProductInfo myProductInfo, PaymentInfo myPaymentInfo) { //U4.SeqDiagram :27
        //print
    }
}

class MyProduct{ //class 3
    public ArrayList<MyProductInfo> myProductInfo = new ArrayList<>();  
    public DBConnect dbConnect = new DBConnect(); //private -> public
    public Refund refund = new Refund();
    public Exchange exchange = new Exchange();
    public String strData = new String();
    
    public void showMyProductDetail(MyProductInfo myProductInfo) throws ParseException {
    	//U4.SeqDiagram :16, add-error : not in class-diagram
        ShowMyProductDetail showMyProductDetail = new ShowMyProductDetail(); //U4.SeqDiagram : 15
    	String data1 = showMyProductDetail.getMyProductInfo(myProductInfo);//U4.SeqDiagram :17
        String data2 = showMyProductDetail.getPaymentInfo(myProductInfo);//U4.SeqDiagram :21
        
        if(data1.contains("error")||data2.contains("error")) { //U4.SeqDiagram :24
        	showMyProductDetail.showProductError(data1, data2);	//U4.SeqDiagram :24, add : showProductError()
        }
        else {
        	showMyProductDetail.myProductInfo = showMyProductDetail.productParser(data1);	//U4.SeqDiagram :25
        	showMyProductDetail.paymentInfo = showMyProductDetail.paymentParser(data2);	//U4.SeqDiagram :26
        	showMyProductDetail.showProductDetail(showMyProductDetail.myProductInfo,showMyProductDetail.paymentInfo);
        	//U4.SeqDiagram :27
        }
        this.dbConnect = null; //U4.SeqDiagram :28
    }

    public String getUsed() {	//U3.SeqDiagram : 9
        return this.dbConnect.executeQuery("query");	//U3.SeqDiagram : 10, 11
    }
    public String getUnused() {	//U3.SeqDiagram : 3
        return this.dbConnect.executeQuery("query");
        //U3.SeqDiagram : 4, 5, jump to Class main
    }
    public void showResult(ArrayList<MyProductInfo> myProductInfo) {	//U3.SeqDiagram : 8, 14
    	System.out.println(myProductInfo);
    }
    public void showErrorResult(String error) {	//U3.SeqDiagram : 6, 12
        System.out.println(error);
    }
    public ArrayList<MyProductInfo> dataParser(String strData) { //U3.SeqDiagram 7, 13
        ArrayList<MyProductInfo> parsedData = new ArrayList<>();
        MyProductInfo tmpData = new MyProductInfo();

        /*Parse from JSON String*/
        
        try {
			JSONParser jParse = new JSONParser();
	        JSONObject jObj = (JSONObject)jParse.parse(strData);
	        JSONArray jArray = (JSONArray)jObj.get("myProducts");
	
	        for(int jArrIndex = 0 ; jArrIndex < jArray.size();jArrIndex++) {
	            JSONObject productInfo = (JSONObject)jArray.get(jArrIndex);
	            tmpData.strReceiver = (String)productInfo.get("strReceiver");
	            tmpData.strSender = (String)productInfo.get("strSender");
	            tmpData.nPaymentCode = (Integer)productInfo.get("nPaymentCode");
	            tmpData.nExpiredDate = (Integer)productInfo.get("nExpiredDate");
	            tmpData.isUsed = (Boolean)productInfo.get("isUsed");
	            parsedData.add(tmpData);
	        }
        } catch(ParseException e) { e.printStackTrace(); }
        tmpData = null;
        return parsedData;
    }
    public void dataIndexing(ArrayList<MyProductInfo> myProductList) { //U3.SeqDiagram : 7
    	//add : for init data
    	ArrayList<MyProductInfo> parsedList = new ArrayList<>();
    	int arrMyProductListIndex = 0;
    	
    	parsedList = this.dataParser(this.strData); //U3.SeqDiagram
    	for(arrMyProductListIndex = 0; arrMyProductListIndex < parsedList.size(); arrMyProductListIndex++) { //U3.SeqDiagram
    		this.myProductInfo.add(parsedList.get(arrMyProductListIndex)); //U3.SeqDiagram
    	}
    	parsedList = null;
    }
}

class ProductList{ //class 1
    public ArrayList<ProductData> productDataList;
    private DBConnect dbConnect = new DBConnect();
    private ShowProductDetail showProductDetail; 
    private int nPriceRange;
    private String strSortInfo;
    private String strCategories;
    private String strSearchTerm;
    public String strData; //error : public
    public int nProduct; //add : choose arraylist

    public String getProductList() { //U1.SeqDiagram : 7
        String strGetDataQuery = "__strGetDataQuery__"; 
        return this.dbConnect.executeQuery(strGetDataQuery); //U1.SeqDiagram : 8, jump to class main
    }
    public ArrayList<ProductData> dataParser(String data){ //U1.SeqDiagram :11 , private->public
        ArrayList<ProductData> parsedData = new ArrayList<>();
        ProductData tmpData = new ProductData();
        
        /*Parse from JSON String*/
        
        try {
			JSONParser jParse = new JSONParser();
	        JSONObject jObj = (JSONObject)jParse.parse(data);
	        JSONArray jArray = (JSONArray)jObj.get("ProductDataList");
	
	        for(int jArrIndex = 0 ; jArrIndex < jArray.size();jArrIndex++) {
	            JSONObject productData = (JSONObject)jArray.get(jArrIndex);
	            
	            tmpData.strProductName = (String)productData.get("strProductName");
	            tmpData.strProductImage = (String)productData.get("strProductImage");
	            tmpData.strProductBrand = (String)productData.get("strProductBrand");
	            tmpData.strProductDescription = (String)productData.get("strProductDescription");
	            tmpData.nProductCode = (Integer)productData.get("nProductCode");
	            tmpData.nProductPrice = (Integer)productData.get("nProductPrice");

	            parsedData.add(tmpData);
	        }
        } catch(ParseException e) { e.printStackTrace(); }
        tmpData = null;
        return parsedData;
    }
    public void setCategories() { //U1.SeqDiagram : 4, private -> public
        try (Scanner scanner = new Scanner(System.in)) {
			System.out.print("input category ");
			this.strCategories = scanner.nextLine();
		}
    }
    public void setPriceRange() { //U1.SeqDiagram : 13, private -> public
        try (Scanner scanner = new Scanner(System.in)) {
			System.out.print("input price range (0, 1, 2, 3)");
			this.nPriceRange = scanner.nextInt();
		}
        if(this.nPriceRange == 0) {// 1 ~ 9,999
        	for(int nReIndex = 0 ; nReIndex < this.productDataList.size(); nReIndex++) {
        		if(this.productDataList.get(nReIndex).nProductPrice > 0 && this.productDataList.get(nReIndex).nProductPrice < 10000) {
        			//print
        		}
        	}
        }
        else if(this.nPriceRange == 1) {// 10,000 ~ 29,999
        	for(int nReIndex = 0 ; nReIndex < this.productDataList.size(); nReIndex++) {
        		if(this.productDataList.get(nReIndex).nProductPrice >= 10000 && this.productDataList.get(nReIndex).nProductPrice < 30000) {
        			//print
        		}
        	}
        }
        else if(this.nPriceRange == 2) {// 30,000 ~ 49,999
        	for(int nReIndex = 0 ; nReIndex < this.productDataList.size(); nReIndex++) {
        		if(this.productDataList.get(nReIndex).nProductPrice >= 30000 && this.productDataList.get(nReIndex).nProductPrice < 50000) {
        			//print
        		}
        	}
        }
        else if(this.nPriceRange == 3) {//50,000 ~  
        	for(int nReIndex = 0 ; nReIndex < this.productDataList.size(); nReIndex++) {
        		if(this.productDataList.get(nReIndex).nProductPrice > 50000) {
        			//print
        		}
        	}
        }
    }
    public void setSortingType() { //U1.SeqDiagram : 15,  private -> public
        try (Scanner scanner = new Scanner(System.in)) {
			System.out.print("input sortingType : asc, desc");
			this.strSortInfo = scanner.nextLine();
		}
        if(this.strSortInfo == "asc") {
        	ArrayList<Integer> ASC = new ArrayList<>();
        	ArrayList<Integer> nIndex = new ArrayList<>();
        	int nTmp, nTmpIdx;
        	int nListIndex, nSubListIndex;

        	for(nListIndex = 0 ; nListIndex < this.productDataList.size(); nListIndex++) {
        		ASC.add(this.productDataList.get(nListIndex).nProductPrice);
        		nIndex.add(nListIndex);
        	}
        	for(nListIndex = 0 ; nListIndex < this.productDataList.size(); nListIndex++) {
        		for(int subListIndex = 0 ; nListIndex < this.productDataList.size()-nListIndex-1;subListIndex++) {
        			if(ASC.get(subListIndex) > ASC.get(subListIndex+1)) {
        					nTmp = ASC.get(subListIndex);
        					nTmpIdx = nIndex.get(subListIndex);
        					ASC.set(subListIndex, ASC.get(subListIndex+1));
        					nIndex.set(subListIndex, nIndex.get(subListIndex)+1);
        					ASC.set(subListIndex+1, nTmp);
        					nIndex.set(subListIndex+1, nTmpIdx);
        			}
        		}
        	} ASC = null;
        	for(nListIndex = 0 ; nListIndex < this.productDataList.size();nListIndex++) {
        		//print this.productDataList.get(nIndex.get(nListIndex))
        	} nIndex = null;
        }
        else if(this.strSortInfo == "desc") {
        	ArrayList<Integer> DESC = new ArrayList<>();
        	ArrayList<Integer> nIndex = new ArrayList<>();
        	int nTmp, nTmpIdx;
        	int nListIndex, nSubListIndex;

        	for(nListIndex = 0 ; nListIndex < this.productDataList.size(); nListIndex++) {
        		DESC.add(this.productDataList.get(nListIndex).nProductPrice);
        		nIndex.add(nListIndex);
        	}
        	for(nListIndex = 0 ; nListIndex < this.productDataList.size(); nListIndex++) {
        		for(int subListIndex = 0 ; nListIndex < this.productDataList.size()-nListIndex-1;subListIndex++) {
        			if(DESC.get(subListIndex) < DESC.get(subListIndex+1)) {
        					nTmp = DESC.get(subListIndex);
        					nTmpIdx = nIndex.get(subListIndex);
        					DESC.set(subListIndex, DESC.get(subListIndex+1));
        					nIndex.set(subListIndex, nIndex.get(subListIndex)+1);
        					DESC.set(subListIndex+1, nTmp);
        					nIndex.set(subListIndex+1, nTmpIdx);
        			}
        		}
        	} DESC = null;
        	for(nListIndex = 0 ; nListIndex < this.productDataList.size();nListIndex++) {
        		//print this.productDataList.get(nIndex.get(nListIndex))
        	} nIndex = null;
        }
    }
    public void setSearchTerm() { //U1.SeqDiagram : 6, private -> public
        try (Scanner scanner = new Scanner(System.in)) {
			System.out.print("input searchTerm");
			this.strSearchTerm = scanner.nextLine();
		}
    }
    public void showProductList(ArrayList<ProductData> productDataList) { //U1.SeqDiagram : 16
    	for(int i  = 0 ; i < productDataList.size();i++) { 	//U1.SeqDiagram : 16
    		//print productDataList.get(i)    //U1.SeqDiagram : 16
    	}
    	
    	try(Scanner scanner = new Scanner(System.in)){
    		this.nProduct = scanner.nextInt();	//U1.SeqDiagram : 17, jump to Class main
    	}
    }
    public void showProductDetail(ProductData productData) throws ParseException {
    	this.showProductDetail.strData = this.showProductDetail.getProductDetail(productDataList.get(this.nProduct)); 
    	//U4.SeqDiagram : 2, 3, jump to C4.ShowProductDetail
    	
    	if(this.showProductDetail.strData.contains("error")) {	//U4.SeqDiagram : 8
    		this.showProductDetail.showProductError(this.showProductDetail.strData);	//U4.SeqDiagram : 8
    	}
    	else {
    		ProductData parsedData = this.showProductDetail.productParser(this.showProductDetail.strData);//U4.SeqDiagram : 9
    		this.showProductDetail.showProductDetail(parsedData);//U4.SeqDiagram : 10
    		
    		Scanner scanner = new Scanner(System.in);
    		String Pay = scanner.nextLine();	 //U4.SeqDiagram :11 
    		if(Pay == "Pay") { //U4.SeqDiagram :11 , user requestPayment
    			this.showProductDetail.requestPayment(parsedData); //U4.SeqDiagram :13, jump to (U5)C5.Payment
    		}
    	}
    }
    public void dataIndexing(ArrayList<ProductData> productDataList) { 
    	ArrayList<ProductData> parsedList = new ArrayList<>();
    	int arrProductListIndex = 0;
    	
    	parsedList = this.dataParser(this.strData); //U3.SeqDiagram
    	for(arrProductListIndex = 0; arrProductListIndex < parsedList.size(); arrProductListIndex++) { 
    		this.productDataList.add(parsedList.get(arrProductListIndex));
    	}
    	parsedList = null;
    }
}

public class Main { //class main
    public static void main() throws ParseException{// add : main
    	try (Scanner menu = new Scanner(System.in)) {
			int click = menu.nextInt(); 
			
			if(click == 1) {	//U1.SeqDiagram : 1
				ProductList();  //U1.SeqDiagram : 1
			}
			else {				//U3.SeqDiagram : 1
				MyProduct();	//U3.SeqDiagram : 1
			}
		}
    }
    public static void MyProduct() throws ParseException {	//U3.SeqDiagram : 1
        MyProduct myProduct = new MyProduct();
        Scanner menu = new Scanner(System.in); 
        String click = menu.nextLine(); 

        
        if(click == "UNUSED") {		//U3.SeqDiagram : 3
            myProduct.strData = myProduct.getUnused();	//U3.SeqDiagram : 3, jump to C3.MyProduct
            if(myProduct.strData.contains("ERROR")) {	//U3.SeqDiagram : 6
                myProduct.showErrorResult(myProduct.strData);	//U3.SeqDiagram : 6
            }
            else {	//U3.SeqDiagram : 7            	
                myProduct.dataIndexing((ArrayList<MyProductInfo>)myProduct.dataParser(myProduct.strData));
                //U3.SeqDiagram : 7
				myProduct.showResult(myProduct.myProductInfo);//U3.SeqDiagram : 8
			}
        }
        else if(click == "USED") {	//U3.SeqDiagram : 9
        	myProduct.strData = myProduct.getUsed();	//U3.SeqDiagram : 9 , jump to C3.MyProduct
            if(myProduct.strData.contains("ERROR")) {	//U3.SeqDiagram : 12
                myProduct.showErrorResult(myProduct.strData);	//U3.SeqDiagram : 12
            }
            else {
            	myProduct.dataIndexing((ArrayList<MyProductInfo>)myProduct.dataParser(myProduct.strData));
            	//U3.SeqDiagram : 13
				myProduct.showResult(myProduct.myProductInfo);//U3.SeqDiagram : 14
            }
        }
        else if(click == "REFUND") {	//U3.SeqDiagram : 15 , U8.SeqDiagram : 1
            int nPaymentCode = menu.nextInt();
            myProduct.refund.requestRefund(nPaymentCode);	//U3.SeqDiagram : 15, U8.SeqDiagram : 2

        }
        else if(click == "EXCHANGE") {	//U3.SeqDiagram : 16, U7.SeqDiagram : 1
            int nPaymentCode = menu.nextInt();
            myProduct.exchange.requestExchange(nPaymentCode);	//U3.SeqDiagram : 16, U7.SeqDiagram : 2

        }
        else if(click == "SHOW_DETAILS") {	//U3.SeqDiagram : 17
        	int nPaymentCode = menu.nextInt();
        	//add : U3.SeqDiagram :17_1
            myProduct.strData = myProduct.dbConnect.executeQuery("__Query_ShowDetail_include_myProductInfo__"); 
            if(myProduct.strData.contains("ERROR")) {		//add : U3.SeqDiagram :17_1
            	myProduct.showErrorResult(myProduct.strData);		//add : U3.SeqDiagram :17_1
            }
            else {		//add : U3.SeqDiagram :15_1
            	myProduct.dataIndexing((ArrayList<MyProductInfo>)myProduct.dataParser(myProduct.strData));		
            	
            	for(int nIndex = 0 ; nIndex < myProduct.myProductInfo.size();nIndex++) {
            		if(nPaymentCode == myProduct.myProductInfo.get(nIndex).nPaymentCode) {	
            			//add : U3.SeqDiagram :17_1 (user Choose routine)
            			myProduct.showMyProductDetail(myProduct.myProductInfo.get(nPaymentCode)); 
            			//U3.SeqDiagram : 17, U4.SeqDiagram :16
            		}
            	}
            }
        }
        else {
            System.exit(0);
        }
    }
    public static void ProductList() throws ParseException{	//U1.SeqDiagram : 1
        ProductList productList = new ProductList(); //U1.SeqDiagram : 2
        Scanner menu = new Scanner(System.in); 
        String click = menu.nextLine(); 

        if(click == "Category"){			//U1.SeqDiagram : 3
            productList.setCategories();	//U1.SeqDiagram : 4
        }
        else if(click == "searchTerm"){		//U1.SeqDiagram : 5
            productList.setSearchTerm();	//U1.SeqDiagram : 6
        }
        productList.strData = productList.getProductList();	//U1.SeqDiagram : 7~9 , jump to C1.ProductList
        if(productList.strData.contains("error")) { //U1.SeqDiagram : 10
        	System.out.println("error page"); //U1.SeqDiagram : 10
        }
        else {
        	productList.dataIndexing(productList.dataParser(productList.strData)); //U1.SeqDiagram : 11
        	click = menu.nextLine(); 
        	if(click == "PriceRage") { //U1.SeqDiagram : 12
        		productList.setPriceRange(); //U1.SeqDiagram : 13
        	}
        	else if(click == "setSortingType") { //U1.SeqDiagram : 14
        		productList.setSortingType();  //U1.SeqDiagram : 15
         	}
        	productList.showProductList(productList.productDataList); 
        	//U1.SeqDiagram : 16, jump to C1.ProductList
        	if(productList.nProduct != 0) { //U1.SeqDiagram : 18
                productList.showProductDetail(productList.productDataList.get(productList.nProduct)); 
                //U1.SeqDiagram : 18, 
            }//jump to (U4) C4.ShowMyProductDetail
        }
    }
}
