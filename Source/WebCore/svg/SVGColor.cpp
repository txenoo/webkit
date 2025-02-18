/*
 * Copyright (C) 2004, 2005 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005, 2006, 2007 Rob Buis <buis@kde.org>
 * Copyright (C) Research In Motion Limited 2011. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "SVGColor.h"

#include "CSSParser.h"
#include "ExceptionCode.h"
#include "RGBColor.h"
#include "SVGException.h"

namespace WebCore {

SVGColor::SVGColor(SVGColorType colorType)
    : CSSValue(SVGColorClass)
    , m_colorType(colorType)
{
}

SVGColor::SVGColor(ClassType classType, SVGColorType colorType)
    : CSSValue(classType)
    , m_colorType(colorType)
{
}

Ref<RGBColor> SVGColor::rgbColor() const
{
    return RGBColor::create(m_color.rgb());
}

Color SVGColor::colorFromRGBColorString(const String& colorString)
{
    // FIXME: Rename to parseSVGColor? There's already a parseSVGColor in the CSS parser. How is it different?
    // FIXME: Rework CSS parser so it exactly matches what the SVG specification requires?
    // FIXME: Move this out of the SVGColor class?
    // FIXME: Is it really OK to do stripWhitespace here instead of stripLeadingAndTrailingHTMLSpaces?
    return CSSParser::parseColor(colorString.stripWhiteSpace());
}

ExceptionOr<void> SVGColor::setRGBColor(const String&)
{
    // The whole SVGColor interface is deprecated in SVG 1.1 (2nd edition).
    // Since the setters are the most problematic part, we removed the support for those first.
    return Exception { NO_MODIFICATION_ALLOWED_ERR };
}

ExceptionOr<void> SVGColor::setRGBColorICCColor(const String&, const String&)
{
    return Exception { NO_MODIFICATION_ALLOWED_ERR };
}

ExceptionOr<void> SVGColor::setColor(unsigned short, const String&, const String&)
{
    return Exception { NO_MODIFICATION_ALLOWED_ERR };
}

String SVGColor::customCSSText() const
{
    switch (m_colorType) {
    case SVG_COLORTYPE_UNKNOWN:
        return String();
    case SVG_COLORTYPE_RGBCOLOR_ICCCOLOR:
    case SVG_COLORTYPE_RGBCOLOR:
        // FIXME: No ICC color support.
        return m_color.cssText();
    case SVG_COLORTYPE_CURRENTCOLOR:
        if (m_color.isValid())
            return m_color.cssText();
        return ASCIILiteral("currentColor");
    }

    ASSERT_NOT_REACHED();
    return String();
}

SVGColor::SVGColor(ClassType classType, const SVGColor& cloneFrom)
    : CSSValue(classType, /*isCSSOMSafe*/ true)
    , m_color(cloneFrom.m_color)
    , m_colorType(cloneFrom.m_colorType)
{
}

Ref<SVGColor> SVGColor::cloneForCSSOM() const
{
    return adoptRef(*new SVGColor(SVGColorClass, *this));
}

bool SVGColor::equals(const SVGColor& other) const
{
    return m_colorType == other.m_colorType && m_color == other.m_color;
}

}
