<?php

/**
 * @file
 * Preprocessors and theme functions of the Superfish module.
 */

use Drupal\Component\Render\FormattableMarkup;
use Drupal\Component\Utility\Html;
use Drupal\Core\Language\LanguageInterface;
use Drupal\Core\Menu\InaccessibleMenuLink;
use Drupal\Core\Template\Attribute;
use Drupal\Core\Url;

/**
 * Prepares variables for the Superfish menu template.
 *
 * Default template: superfish.html.twig.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #menu_name, #html_id, #settings, #tree
 *     - menu_name: Unique menu identifier.
 *     - html_id: Unique HTML ID.
 *     - settings: Menu block settings.
 *     - tree: The menu tree.
 *
 * @see superfish.html.twig
 */
function template_preprocess_superfish(array &$variables) {
  $element = $variables['element'];

  $menu_items_rendered = [
    '#theme' => 'superfish_menu_items',
    '#menu_name' => $element['#menu_name'],
    '#tree' => $element['#tree'],
    '#settings' => $element['#settings'],
    '#cloned_parent' => FALSE,
  ];

  $direction = \Drupal::languageManager()->getCurrentLanguage()->getDirection();
  $menu_classes = ['menu', 'sf-menu'];
  $menu_classes[] = 'sf-' . $element['#menu_name'];
  $menu_classes[] = 'sf-' . $element['#settings']['menu_type'];
  $menu_classes[] = 'sf-style-' . $element['#settings']['style'];

  $menu_classes[] = ($direction === LanguageInterface::DIRECTION_RTL) ? 'rtl' : '';
  if (strpos($element['#settings']['ulclass'], ' ') !== FALSE) {
    $l = explode(' ', $element['#settings']['ulclass']);
    foreach ($l as $c) {
      $menu_classes[] = Html::cleanCssIdentifier($c);
    }
  }
  else {
    $menu_classes[] = Html::cleanCssIdentifier($element['#settings']['ulclass']);
  }
  $menu_classes = implode(' ', superfish_array_filter($menu_classes));

  $variables['id'] = $element['#html_id'];
  $variables['menu_classes'] = $menu_classes;
  $variables['menu_items'] = $menu_items_rendered;

}

/**
 * Prepares variables for Superfish menu items templates.
 *
 * Default template: superfish-menu-items.html.twig.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #tree, #settings, #cloned_parent
 *     - tree: The menu tree.
 *     - menu_name: Unique menu identifier.
 *     - settings: Block settings
 *     - cloned_parent: Cloned sub-menu parent link.
 *
 * @see superfish-menu-items.html.twig
 */
function template_preprocess_superfish_menu_items(array &$variables) {

  $element = $variables['element'];

  // Keep $sfsettings untouched as we need to pass it to the child menus.
  $settings = $sfsettings = $element['#settings'];

  $variables['menu_items'] = [];

  $menu = $element['#tree'];

  // sfTouchscreen.
  // Adding cloned parent to the sub-menu tree.
  // Note, it is always false if it's not a sub-menu.
  if ($element['#cloned_parent'] !== FALSE) {
    array_unshift($menu, $element['#cloned_parent']);
  }

  $active_trails = \Drupal::service('menu.active_trail')
    ->getActiveTrailIds($element['#menu_name']);

  foreach ($menu as $menu_item) {
    // Menu link properties.
    $link = $menu_item->link->getPluginDefinition();

    if (NULL !== $menu_item->link &&
        !($menu_item->link instanceof InaccessibleMenuLink) && $link['enabled']) {

      $item_class = $link_class = [];
      $multicolumn_wrapper = $multicolumn_column = $multicolumn_content = $nolink = FALSE;

      $item = [
        'id'            => $link['id'],
        'text'          => $menu_item->link->getTitle(),
        'description'   => $menu_item->link->getDescription(),
        'url'           => $menu_item->link->getUrlObject(),
        'enabled'       => $link['enabled'],
        'expanded'      => $sfsettings['expanded'] ? $link['expanded'] : TRUE,
        'options'       => $link['options'],
        'subtree'       => $menu_item->subtree,
        'depth'         => $menu_item->depth,
        'hasChildren'   => $menu_item->hasChildren,
        'inActiveTrail' => $menu_item->inActiveTrail,
      ];

      if ($item['url']->isRouted()) {
        // Adding the "is-active" class.
        $host = \Drupal::request()->getHttpHost();
        $request_uri = \Drupal::request()->getRequestUri();
        $current_url = Url::fromRoute('<current>');
        $current_path = $current_url->toString();
        $link_url = $item['url']->toString();
        // Anchor links.
        if (strpos($link_url, '#') !== FALSE) {
          $link_url = explode('#', $link_url);
          $link_url = $link_url[0];
        }

        if ($link_url == $current_path || $link_url == $request_uri ||
            $link_url == $host . $request_uri) {
          $link_class[] = 'is-active';
        }
        $nolink = $item['url']->getRouteName() === '<nolink>' ? TRUE : FALSE;
      }

      // Adding the necessary "active-trail" class.
      if ($item['inActiveTrail'] ||
          array_key_exists($item['id'], $active_trails) ||
          ($menu_item->link->getUrlObject()->isRouted() &&
          $menu_item->link->getUrlObject()->getRouteName() == '<front>' &&
          \Drupal::service('path.matcher')->isFrontPage())) {
        $item_class[] = 'active-trail';
      }

      // Add menu link depth classes to the <li> element and its link.
      if ($settings['itemdepth']) {
        $link_class[] = 'sf-depth-' . $item['depth'];
        $item_class[] = 'sf-depth-' . $item['depth'];
      }
      // Indicates a cloned parent, i.e. does not exist in the actual menu tree.
      $item_class[] = $element['#cloned_parent'] ? 'sf-clone-parent' : '';

      // Adding custom <li> classes.
      if (strpos($settings['liclass'], ' ') !== FALSE) {
        $l = explode(' ', $settings['liclass']);
        foreach ($l as $c) {
          $item_class[] = Html::cleanCssIdentifier($c);
        }
      }
      else {
        $item_class[] = Html::cleanCssIdentifier($settings['liclass']);
      }

      // Adding custom link classes.
      if (strpos($settings['hlclass'], ' ') !== FALSE) {
        $l = explode(' ', $settings['hlclass']);
        foreach ($l as $c) {
          $link_class[] = Html::cleanCssIdentifier($c);
        }
      }
      else {
        $link_class[] = Html::cleanCssIdentifier($settings['hlclass']);
      }

      // Add a class to external links.
      $link_class[] = isset($item['options']['external']) ? 'sf-external' : '';

      // Inserting link description (the "title" attribute) into the text.
      if ($settings['add_linkdescription'] && !empty($item['description'])) {
        $link_text = '@text <span class="sf-description">@description</span>';
        $link_text_replace = [
          '@text'        => $item['text'],
          '@description' => $item['description'],
        ];
      }
      else {
        $link_text = '@text';
        $link_text_replace = [
          '@text' => $item['text'],
        ];
      }

      // Hiding link descriptions (the "title" attribute).
      if ($settings['hide_linkdescription']) {
        $item['options']['attributes']['title'] = '';
      }

      // Sub-menu.
      if ($item['hasChildren'] && $item['subtree'] && $item['expanded']) {

        // Multi-column sub-menus.
        if ($settings['multicolumn']) {
          $multicolumn_wrapper = $item['depth'] == $settings['multicolumn_depth'];
          $multicolumn_column = $item['depth'] == $settings['multicolumn_depth'] + 1;
          $multicolumn_content = $item['depth'] >= $settings['multicolumn_depth'] &&
            $item['depth'] <= $settings['multicolumn_levels'];
        }

        // sfTouchscreen.
        // Preparing the cloned parent links to be added to the sub-menus.
        if ($settings['clone_parent'] && $item['subtree'] && !$nolink) {
          $cloned_parent = $menu_item;
          $cloned_parent->subtree = [];
        }
        else {
          $cloned_parent = FALSE;
        }

        // Render the sub-menu.
        $children = [
          '#theme'         => 'superfish_menu_items',
          '#menu_name'     => $element['#menu_name'],
          '#tree'          => $item['subtree'],
          '#settings'      => $sfsettings,
          '#cloned_parent' => $cloned_parent,
        ];

        if ($item['subtree']) {
          // Adding some more classes.
          $item_class[] = $multicolumn_column ? 'sf-multicolumn-column' : '';
          $item_class[] = $link_class[] = 'menuparent';
        }
      }
      else {
        $children = '';
        $item_class[] = 'sf-no-children';
      }

      // Preparing <li> classes for the theme.
      $item_class = implode(' ', superfish_array_filter($item_class));

      // Merging link classes.
      if (isset($item['options']['attributes']['class'])) {
        $link_class_current = $item['options']['attributes']['class'];
        if (!is_array($link_class_current)) {
          $link_class_current = [$link_class_current];
        }
        $link_class = array_merge(
          $link_class_current,
          superfish_array_filter($link_class)
        );
      }
      $item['options']['attributes']['class'] = superfish_array_filter($link_class);

      // Dirty fix! to only add a "menuparent" class.
      $item['options_menuparent'] = $item['options'];
      $item['options_menuparent']['attributes']['class'][] = 'menuparent';
      if ($nolink) {
        $item['options_menuparent']['attributes']['class'][] = 'nolink';
        $item['options']['attributes']['class'][] = 'nolink';
      }
      $link_element = [
        '#type' => 'link',
        '#title' => new FormattableMarkup($link_text, $link_text_replace),
        '#url' => $item['url'],
        '#options' => $item['options'],
      ];
      $link_element_menuparent = [
        '#type' => 'link',
        '#title' => new FormattableMarkup($link_text, $link_text_replace),
        '#url' => $item['url'],
        '#options' => $item['options_menuparent'],
      ];

      $item_attributes = new Attribute();
      if (isset($item['options']['item_attributes'])) {
        foreach ($item['options']['item_attributes'] as $name => $value) {
          $value = trim($value);
          if ($value) {
            $item_attributes->offsetSet($name, $value);
          }
        }
      }

      $id = Html::getUniqueId($element['#menu_name'] . '-' . $item['id']);
      if (!$item_attributes->offsetGet('id')) {
        $item_attributes->offsetSet('id', $id);
      }

      if ($item_class) {
        $item_attributes->offsetSet('class', trim($item_attributes->offsetGet('class') . ' ' . $item_class));
      }

      $variables['menu_items'][] = [
        'attributes'          => $item_attributes,
        'link'                => $link_element,
        'link_menuparent'     => $link_element_menuparent,
        'children'            => $children,
        'multicolumn_wrapper' => $multicolumn_wrapper,
        'multicolumn_content' => $multicolumn_content,
        'multicolumn_column'  => $multicolumn_column,
      ];
    }
  }
}
