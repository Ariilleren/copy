
var sQuery = '<?php echo $sQuery; ?>';



function doAlert() {
    let nameField = document.getElementsByClassName("sis")[0];
     let emailField = document.getElementsByClassName("odr")[0];
     let emailPattern = '@';
     let numberField = document.getElementsByClassName("dpt")[0];
   let length1 = numberField.value.length;
   nameField.focus()
   if ((emailField.value.includes(emailPattern)) && ((length1 === 12) && (!(emailField.value === "")) && (!(nameField.value === "")) && (!(numberField.value === "+7")))) {
       alert("Уважаемый " + nameField.value + "! Спасибо за оставленные данные, мы свяжемся с вами по телефону " + numberField.value + " и отправим письмо на " + emailField.value)
   }
   else {
       if ((!(length1 === 12)) && (!(emailField.value.includes(emailPattern))) && (!(emailField.value === "")) && (!(nameField.value === "")) && (!(numberField.value === "+7"))) {
           alert("Данные формы введены неверно: в поле e-mail неверно указан адрес почты, в поле Телефон неверно указан номер телефона")
   }
       else if ((!(emailField.value.includes(emailPattern))) && (!(emailField === "")) && (!(nameField.value === "")) && (!(numberField.value === "+7"))) {
           alert("Данные формы введены неверно: в поле e-mail неверно указан адрес почты")
   }
       else if ((!(length1 === 12)) && (!(emailField.value === "")) && (!(nameField.value === "")) && (!(numberField.value === "+7"))) {
           alert("Данные формы введены неверно: в поле Телефон неверно указан номер телефона")
   }
   }
   }

// function Show() {
//     let Elm = document.getElementsByClassName("text")[0];
//     Elm.style.display = "block";
// }

$(document).ready(function Show(){
     $("#knopka").click(function () {
         if ($("#text").is(":hidden")) {
             $("#text").show("slow");
         } else {
             $("#text").hide("slow");
         }
         return false;
     });
 });
    