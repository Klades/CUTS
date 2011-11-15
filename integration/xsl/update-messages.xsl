<?xml version="1.0" encoding="utf-8" standalone="yes"?>
<xsl:stylesheet version="2.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns="http://www.w3.org/1999/xhtml">
  <xsl:output method="xml" indent="yes" omit-xml-declaration="no"
              version="1.0"  encoding="utf-8" standalone="yes"
              cdata-section-elements="message" />

  <xsl:template match="/">
    <xsl:apply-templates />
  </xsl:template>

  <xsl:template match="message[@priority='info']">
    <xsl:copy>
      <xsl:choose>
        <xsl:when test="contains(child::node()[1], ': warning C')" >
          <xsl:attribute name="priority">warn</xsl:attribute>
        </xsl:when>
        <xsl:when test="contains(child::node()[1], ': warning PRJ')" >
          <xsl:attribute name="priority">warn</xsl:attribute>
        </xsl:when>
        <xsl:when test="contains(child::node()[1], ': error C')" >
          <xsl:attribute name="priority">error</xsl:attribute>
        </xsl:when>
        <xsl:when test="contains(child::node()[1], ': error PRJ')">
          <xsl:attribute name="priority">error</xsl:attribute>
        </xsl:when>
        <xsl:when test="contains(child::node()[1], ': fatal error C')" >
          <xsl:attribute name="priority">error</xsl:attribute>
        </xsl:when>
        <xsl:when test="contains(child::node()[1], ': fatal error PRJ')">
          <xsl:attribute name="priority">error</xsl:attribute>
        </xsl:when>
        <xsl:when test="contains(child::node()[1], ': fatal error LNK')">
          <xsl:attribute name="priority">error</xsl:attribute>
        </xsl:when>
        <xsl:otherwise>
          <xsl:attribute name="priority"><xsl:value-of select="@priority"/></xsl:attribute>
        </xsl:otherwise>
      </xsl:choose>

      <xsl:value-of select="." />
    </xsl:copy>
  </xsl:template>

  <!-- xsl:template match="message[@priority='warn']">
    <xsl:copy>
      <xsl:choose>
        <xsl:when test="contains(child::node()[1], 'MPC_ROOT was set to')">
          <xsl:attribute name="priority">info</xsl:attribute>
        </xsl:when>
        <xsl:otherwise>
          <xsl:attribute name="priority">
            <xsl:value-of select="@priority"/>
          </xsl:attribute>
        </xsl:otherwise>
      </xsl:choose>

      <xsl:value-of select="." />
    </xsl:copy>
  </xsl:template-->

  <xsl:template match="message[@priority='error']">
    <xsl:copy>
      <xsl:choose>
        <xsl:when test="contains(child::node()[1], 'Result: ')">
          <xsl:attribute name="priority">info</xsl:attribute>
        </xsl:when>
        <xsl:otherwise>
          <xsl:attribute name="priority">
            <xsl:value-of select="@priority"/>
          </xsl:attribute>
        </xsl:otherwise>
      </xsl:choose>

      <xsl:value-of select="." />
    </xsl:copy>
  </xsl:template>

  <xsl:template match="*|@*">
    <xsl:copy>
      <xsl:apply-templates select="@*"/>
      <xsl:apply-templates />
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>
