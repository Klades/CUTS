<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" omit-xml-declaration="no" doctype-system="mga.dtd" indent="yes"/>

  <!--
        apply all templates starting from the root
    -->
  <xsl:template match="/">
    <xsl:apply-templates />
  </xsl:template>

  <!--
        Purpose:

        This template will convert the PICML project to a CHAOS
        project. Right now, we do not know what the UUID of the
        project, and will leave it up to the end-user to fix it.
    -->
  <xsl:template match="project[@metaname='PICML']">

    <!-- copy the name of the element -->
    <xsl:element name="{name()}">
      <xsl:for-each select="@*">
        <xsl:choose>
          <xsl:when test="name()='metaname'">
            <!-- treat its kind attribute specially -->
            <xsl:attribute name="metaname">CHAOS</xsl:attribute>
          </xsl:when>

          <xsl:otherwise>
            <xsl:copy />
          </xsl:otherwise>
        </xsl:choose>
      </xsl:for-each>

      <!-- copy the remaining nodes of the project -->
      <xsl:apply-templates />
    </xsl:element>
  </xsl:template>

  <!--
        Default transformation for all nodes
    -->
  <xsl:template match="*|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates />
    </xsl:copy>
  </xsl:template>

</xsl:stylesheet>
