/*
 * Copyright (c) 2011, the Dart project authors.
 * 
 * Licensed under the Eclipse Public License v1.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 * 
 * http://www.eclipse.org/legal/epl-v10.html
 * 
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */
package com.google.dart.tools.ui.internal.util;

import com.google.dart.engine.element.Element;
import com.google.dart.tools.core.model.DartElement;
import com.google.dart.tools.ui.DartUI;
import com.google.dart.tools.ui.DartUIMessages;
import com.google.dart.tools.ui.internal.actions.SelectionConverter;
import com.google.dart.tools.ui.internal.typehierarchy.TypeHierarchyViewPart;

import org.eclipse.core.runtime.Assert;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.IWorkbenchWindow;

public class OpenTypeHierarchyUtil {

  public static TypeHierarchyViewPart open(DartElement[] candidates, IWorkbenchWindow window) {
    Assert.isTrue(candidates != null && candidates.length != 0);

    DartElement input = null;
    if (candidates.length > 1) {
      String title = DartUIMessages.OpenTypeHierarchyUtil_selectionDialog_title;
      String message = DartUIMessages.OpenTypeHierarchyUtil_selectionDialog_message;
      input = SelectionConverter.selectJavaElement(candidates, window.getShell(), title, message);
    } else {
      input = candidates[0];
    }
    if (input == null) {
      return null;
    }

    return openInViewPart(window, input);
  }

  public static TypeHierarchyViewPart open(Element element, IWorkbenchWindow window) {
    if (element != null) {
      return openInViewPart(window, element);
    }
    return null;
  }

  private static TypeHierarchyViewPart openInViewPart(IWorkbenchWindow window, Object input) {
    IWorkbenchPage page = window.getActivePage();
    try {
      TypeHierarchyViewPart result = (TypeHierarchyViewPart) page.findView(DartUI.ID_TYPE_HIERARCHY);
      result = (TypeHierarchyViewPart) page.showView(DartUI.ID_TYPE_HIERARCHY);
      result.setInputElement(input);
      return result;
    } catch (CoreException e) {
      ExceptionHandler.handle(
          e,
          window.getShell(),
          DartUIMessages.OpenTypeHierarchyUtil_error_open_view,
          e.getMessage());
    }
    return null;
  }

  private OpenTypeHierarchyUtil() {
  }
}
