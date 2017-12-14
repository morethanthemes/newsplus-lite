  /**
  * Add Javascript - Node features JS
  */
jQuery(document).ready(function($) {
  if (jQuery("#affix").length>0) {

    var affixBottom = $("#footer").outerHeight(true)
    + $("#subfooter").outerHeight(true)
    + $("#main-content").outerHeight(true)
    - $(".block-system-main-block").outerHeight(true),
    affixTop = $("#affix").offset().top;

    //The admin overlay menu height
    var headerHeight = $("#header").outerHeight(true);
    var adminHeight = parseInt($('body').css('paddingTop'));
    var topValue = adminHeight + headerHeight + 15;

    //We select the highest of the 2 adminHeight OR fixedheaderHeight to use
    if (headerHeight > adminHeight) {
      fixedAffixTop = headerHeight;
    } else {
      fixedAffixTop = adminHeight;
    }

    function initializeAffix(topAffix) {
      if ($(".fixed-header-enabled").length>0) {
        affixBottom = affixBottom + headerHeight - fixedAffixTop - adminHeight + 15;
        initAffixTop = topAffix - adminHeight - headerHeight - 15; //The fixedAffixTop is added as padding on the page so we need to remove it from affixTop
      } else {
        affixBottom = affixBottom;
        initAffixTop = topAffix - adminHeight - 15; // The adminHeight is added as padding on the page so we need to remove it from affixTop
      }
      $("#affix").affix({
        offset: {
          top: initAffixTop,
          bottom: affixBottom
        }
      });
    }

    //The internal banner element is rendered after it is ready so initially it does not have height that can calculated
    //Therefore we manually add the height when we know it or we wait a few seconds to when its height is not known
    initializeAffix(affixTop);

    $("#affix").on("affixed.bs.affix", function () {
      //We set through JS the inline style top position
      if ($(".fixed-header-enabled").length>0) {
        $("#affix").css("top", (headerHeight+adminHeight)+"px");
      } else {
        $("#affix").css("top", (adminHeight)+"px");
      }
    });

  }
});

