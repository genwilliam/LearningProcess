// JavaScript Document

/*通过ID获取HTML对象的通用方法，使用$代替函数名称*/
function $(elementId){
	return document.getElementById(elementId);
	}
	
/*当鼠标放在通行证用户名文本框时，提示文本及样式*/	
function userNameFocus(){
	var userNameId=$("userNameId");
	userNameId.className="import_prompt";
	userNameId.innerHTML="1、由字母、数字、下划线、点、减号组成<br/>2、只能以数字、字母开头或结尾，且长度为4-18";
	}
	
/*当鼠标离开通行证用户名文本框时，提示文本及样式*/	
function userNameBlur(){
	var userName=$("userName");
	var userNameId=$("userNameId");
	var reg=/^[0-9a-zA-Z][0-9a-zA-Z_.-]{2,16}[0-9a-zA-Z]$/;
	if(userName.value==""){
		userNameId.className="error_prompt";
		userNameId.innerHTML="通行证用户名不能为空，请输入通行证用户名";
		return false;
		}
	if(reg.test(userName.value)==false){
		userNameId.className="error_prompt";
	    userNameId.innerHTML="1、由字母、数字、下划线、点、减号组成<br/>2、只能以数字、字母开头或结尾，且长度为4-18";
		return false;
		}
		userNameId.className="ok_prompt";
	    userNameId.innerHTML="通行证用户名输入正确";
		return true;
	}

/*当鼠标放在密码文本框时，提示文本及样式*/	
function pwdFocus(){
	var pwdId=$("pwdId");
	pwdId.className="import_prompt";
	pwdId.innerHTML="密码长度为6-16";
	}
	
/*当鼠标离开密码文本框时，提示文本及样式*/	
function pwdBlur(){
	var pwd=$("pwd");
	var pwdId=$("pwdId");
	if(pwd.value==""){
		pwdId.className="error_prompt";
		pwdId.innerHTML="密码不能为空，请输入密码";
		return false;
		}
	if(pwd.value.length<6 || pwd.value.length>16){
		pwdId.className="error_prompt";
	    pwdId.innerHTML="密码长度为6-16";
		return false;
		}
		pwdId.className="ok_prompt";
	    pwdId.innerHTML="密码输入正确";
		return true;
	}

	
/*当鼠标离开重复密码文本框时，提示文本及样式*/	
function repwdBlur(){
	var repwd=$("repwd");
	var pwd=$("pwd");
	var repwdId=$("repwdId");
	if(repwd.value==""){
		repwdId.className="error_prompt";
		repwdId.innerHTML="重复密码不能为空，请重复输入密码";
		return false;
		}
	if(repwd.value!=pwd.value){
		repwdId.className="error_prompt";
	    repwdId.innerHTML="两次输入的密码不一致，请重新输入";
		return false;
		}
		repwdId.className="ok_prompt";
	    repwdId.innerHTML="两次密码输入正确";
		return true;
	}
	
/*当鼠标放在昵称文本框时，提示文本及样式*/	
function nickNameFocus(){
	var nickNameId=$("nickNameId");
	nickNameId.className="import_prompt";
	nickNameId.innerHTML="1、包含汉字、字母、数字、下划线以及@!#$%&*特殊字符<br/>2、长度为4－20个字符<br/>3、一个汉字占两个字符";
	}
	
/*当鼠标离开昵称文本框时，提示文本及样式*/	
function nickNameBlur(){
	var nickName=$("nickName");
	var nickNameId=$("nickNameId");
	var k=0;
	var reg=/^([\u4e00-\u9fa5]|\w|[@!#$%&*])+$/;   // 匹配昵称
	var chinaReg=/[\u4e00-\u9fa5]/g;   //匹配中文字符
	if(nickName.value==""){
		nickNameId.className="error_prompt";
		nickNameId.innerHTML="昵称不能为空，请输入昵称";
		return false;
		}
	if(reg.test(nickName.value)==false){
		nickNameId.className="error_prompt";
	    nickNameId.innerHTML="只能由汉字、字母、数字、下划线以及@!#$%&*特殊字符组成";
		return false;
		}
	
	var len=nickName.value.replace(chinaReg,"ab").length;  //把中文字符转换为两个字母，以计算字符长度
	if(len<4||len>20){
		nickNameId.className="error_prompt";
	    nickNameId.innerHTML="1、长度为4－20个字符<br/>2、一个汉字占两个字符";
		return false;
		}
	
		nickNameId.className="ok_prompt";
	    nickNameId.innerHTML="昵称输入正确";
		return true;
	}	

/*当鼠标放在关联手机号文本框时，提示文本及样式*/	
function telFocus(){
	var telId=$("telId");
	telId.className="import_prompt";
	telId.innerHTML="1、手机号码以13，15，18开头<br/>2、手机号码由11位数字组成";
	}
	
/*当鼠标离开关联手机号文本框时，提示文本及样式*/	
function telBlur(){
	var tel=$("tel");
	var telId=$("telId");
	var reg=/^(13|15|18)\d{9}$/;
	if(tel.value==""){
		telId.className="error_prompt";
		telId.innerHTML="关联手机号码不能为空，请输入关联手机号码";
		return false;
		}
	if(reg.test(tel.value)==false){
		telId.className="error_prompt";
	    telId.innerHTML="关联手机号码输入不正确，请重新输入";
		return false;
		}
		telId.className="ok_prompt";
	    telId.innerHTML="关联手机号码输入正确";
		return true;
	}	


/*当鼠标放在保密邮箱文本框时，提示文本及样式*/	
function emailFocus(){
	var emailId=$("emailId");
	emailId.className="import_prompt";
	emailId.innerHTML="请输入您常用的电子邮箱";
	}
	
/*当鼠标离开保密邮箱文本框时，提示文本及样式*/	
function emailBlur(){
	var email=$("email");
	var emailId=$("emailId");
	var reg=/^\w+@\w+(\.[a-zA-Z]{2,3}){1,2}$/;
	if(email.value==""){
		emailId.className="error_prompt";
		emailId.innerHTML="保密邮箱不能为空，请输入保密邮箱";
		return false;
		}
	if(reg.test(email.value)==false){
		emailId.className="error_prompt";
	    emailId.innerHTML="保密邮箱格式不正确，请重新输入";
		return false;
		}
		emailId.className="ok_prompt";
	    emailId.innerHTML="保密邮箱输入正确";
		return true;
	}	

/*表单提交时验证表单内容输入的有效性*/
function checkForm(){
	  var flagUserName=userNameBlur();
	  var flagPwd=pwdBlur();
	  var flagRepwd=repwdBlur();
	  var flagNickName=nickNameBlur();
	  var flagTel=telBlur();
	  var flagEmail=emailBlur();
	  
	  userNameBlur();
	  pwdBlur();
	  repwdBlur();
	  nickNameBlur();
	  telBlur();
	  emailBlur();
	  
	  if(flagUserName==true &&flagPwd==true &&flagRepwd==true &&flagNickName==true&&flagTel==true&flagEmail==true){
		  return true;
		  }
		else{
			return false;
			}
	
	}



	