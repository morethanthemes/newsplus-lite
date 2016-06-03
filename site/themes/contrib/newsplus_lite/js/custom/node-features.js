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
      var isInitialised = false;

      //The admin overlay menu height
      var headerHeight = $("#header").outerHeight(true);
      var adminHeight = parseInt($('body').css('paddingTop'));
      var topValue = adminHeight + headerHeight + 15;

      var initAffixTop = affixTop - adminHeight - headerHeight - 15;
      function initializeAffix(topAffix) {
        $("#affix").affix({
          offset: {
            top: initAffixTop,
            bottom: affixBottom
          }
        });
        isInitialised = true;
      }

      initializeAffix(initAffixTop);


      function recalcAffixBottom() {
        affixBottom = $("#footer").outerHeight(true)
          + $("#subfooter").outerHeight(true)
          + $("#main-content").outerHeight(true)
          - $(".block-system-main-block").outerHeight(true);
        $("#affix").data("bs.affix").options.offset.bottom = affixBottom;
      }

      $("#affix").on("affixed.bs.affix", function () {
        if (isInitialised) {
          recalcAffixBottom();
        }
        //We set through JS the inline style top position
        if ($(".user-logged-in").length>0) {
          $("#affix").css("top", (topValue)+"px");
        } else {
          $("#affix").css("top", (headerHeight +15)+"px");
        }
      });
    });
  }
});
