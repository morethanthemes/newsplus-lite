  /**
  * Add Javascript - Node features JS
  */
jQuery(document).ready(function($) {
  if (jQuery("#affix").length>0) {
    $(window).load(function() {
      var affixBottom = $("#footer").outerHeight(true)
      + $("#subfooter").outerHeight(true)
      + $("#main-content").outerHeight(true)
      - $(".block-system-main-block").outerHeight(true),
      affixTop = $("#affix").offset().top;

      //The admin overlay menu height
      var adminHeight = 100;

      var initAffixTop = affixTop-adminHeight;
      function initializeAffix(topAffix) {
        $("#affix").affix({
          offset: {
            top: initAffixTop,
            bottom: affixBottom
          }
        });
      }

      initializeAffix(initAffixTop);

      $("#affix").on("affixed.bs.affix", function () {
        //We set through JS the inline style top position
        if ($(".user-logged-in").length>0) {
          $("#affix").css("top", (adminHeight)+"px");
        } else {
          $("#affix").css("top", (15)+"px");
        }
      });
    });
  }
});
