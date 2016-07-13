  /**
  * Add Javascript - Fixed Header
  */
jQuery(document).ready(function($) {
  var preHeaderHeight = $("#pre-header").outerHeight(),
  headerTopHeight = $("#header-top").outerHeight(),
  headerHeight = $("#header").outerHeight();
  $(window).load(function() {
    if(($(window).width() > 767)) {
      $("body").addClass("fixed-header-enabled");
    } else {
      $("body").removeClass("fixed-header-enabled");
    }
  });
  $(window).resize(function() {
    if(($(window).width() > 767)) {
      $("body").addClass("fixed-header-enabled");
    } else {
      $("body").removeClass("fixed-header-enabled");
    }
  });
  $(window).scroll(function() {
    if(($(this).scrollTop() > preHeaderHeight+headerTopHeight) && ($(window).width() > 767)) {
      $("body").addClass("onscroll");
      if ($("#toolbar-administration").length > 0) {
        var adminHeight = $('body').css('paddingTop');
        $("#header").css("top", adminHeight);
      }
      if ($("#page-intro").length > 0) {
        $("#page-intro").css("paddingTop", (headerHeight)+"px");
      } else {
        $("#page").css("paddingTop", (headerHeight)+"px");
      }
    } else {
      $("body").removeClass("onscroll");
      $("#header").css("top", (0)+"px");
      $("#page,#page-intro").css("paddingTop", (0)+"px");
    }
  });
});
